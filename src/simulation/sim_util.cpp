/**
 * @file sim_util.cpp
 *
 * @brief Utility for simulation declaration
 *
 * @author
 *     Lukáš Kurtin
 */

#include "sim_util.h"

Sender* SimUtil::event_sender = nullptr;
std::map<std::pair<std::string, int32_t>, int64_t> SimUtil::scheduled_timers = {};
int64_t SimUtil::time_at_start = 0;
int64_t SimUtil::current_time_ms = 0;
uint32_t SimUtil::timer_index_counter = 0;

bool SimUtil::ableToBeFired(PetriNet& pnet, const std::string& transition_id) {
    //check if transition with this ID exists
    if(pnet.transitions.find(transition_id) == pnet.transitions.end()) {
        printf("Transition doesnt exist.\n");
        return false;
    }
    if(!pnet.transitions.at(transition_id).isEnabled()) {
        printf("Transition is not enabled.\n");
        return false;
    }

    for(auto& pair : pnet.arcs) {
        auto& arc = pair.second;
        //if arc points into this transition
        if(arc.getTargetId() == transition_id) {
            std::string place_source_id = arc.getSourceId();
            int requiredTokens = arc.getWeight();
            
            //finding of the entry point and checking tokens
            bool enough_tokens = false;

            //
            if(auto place = pnet.places.find(place_source_id); place != pnet.places.end()){
                if(place->second.getCurrentTokens() >= requiredTokens) {
                    enough_tokens = true;
                }
            }
            
            //if place was not found or there were not enough tokens, then the transition can not be fired
            if(!enough_tokens) {
                return false;
            }
        }
    }
    //if all entry points were found and none of them failed, then transition is ready to be fired
    return true;
}

bool SimUtil::fire(PetriNet& pnet, const std::string& transition_id) {
    if(!ableToBeFired(pnet, transition_id)) {
        return false;
    }

    //removing tokens
    for(auto& pair : pnet.arcs) {
        auto& arc = pair.second;
        if(arc.getTargetId() == transition_id) {
            std::string place_source_id = arc.getSourceId();
            int tokens_remove = arc.getWeight();

            
            if(auto place = pnet.places.find(place_source_id); place != pnet.places.end()) {
                place->second.setCurrentTokens(place->second.getCurrentTokens() - tokens_remove);
                place->second.setLastTimeChange(current_time_ms);

                getEventSender()->throwEvent(Event::update_tokens_, place_source_id, -tokens_remove);

            }
        }
    }

    //adding of tokens
    for(auto& pair : pnet.arcs) {
        auto& arc = pair.second;
        //if arc exits out of this transition, then it is an exit arc
        if(arc.getSourceId() == transition_id) {
            std::string place_target_id = arc.getTargetId();
            int tokens_add = arc.getWeight();
            
            if(auto place = pnet.places.find(place_target_id); place != pnet.places.end()) {
                place->second.setCurrentTokens(place->second.getCurrentTokens() + tokens_add);
                place->second.setLastTimeChange(current_time_ms);

                getEventSender()->throwEvent(Event::update_tokens_, place_target_id, tokens_add);
            }
        }
    }
    return true;
}

int64_t SimUtil::evaluateTimerState(PetriNet& pnet, std::string& event_name) {
    int64_t next_timer_in = 100000;
    if(scheduled_timers.empty()){
        //fire a non-scheduled timer
        for (auto pair : pnet.getTransitions())
        if(pair.second.isEnabled() &&
            (event_name != ""      && event_name == pair.second.getInputEventName())) 
        {
            if(fire(pnet, pair.first)) {
                // another transition MAY be able to fire now
                event_sender->throwEvent(Event::fire_, pair.first);
            }
            else{
                event_sender->throwEvent(Event::timer_ignored_);
            }
            break;
        }
    }
    else{
        bool network_change = true;
        while(network_change) {
        network_change = false;

        std::map<std::pair<std::string, int32_t>, int64_t>::iterator pair;
        for(pair = scheduled_timers.begin(); pair != scheduled_timers.end();) {
            Transition trans = pnet.transitions.at(pair->first.first);
            std::string trans_id = pair->first.first;
            int64_t timer = pair->second;    

            if((timer <= getNetTime() && trans.isEnabled()) || 
               (event_name != ""      && event_name == trans.getInputEventName())) {

                if(fire(pnet, trans_id)) {
                    // another transition MAY be able to fire now
                    event_sender->throwEvent(Event::fire_, trans_id);
                    network_change = true;
                }
                else{
                    event_sender->throwEvent(Event::timer_ignored_);
                }
                //remove the timer from scheduled timers even if it was not enabled
                scheduled_timers.erase(pair->first);
                if(scheduled_timers.size() == 0){
                    return next_timer_in;
                }
                break;
            }

            //calculate the lowest time until next transition fires
            if(timer > 0 && next_timer_in > timer - getNetTime()) {
                next_timer_in = timer - getNetTime();
            }
            //advance the iterator
            pair++;
        }
        }
    }
    event_name = "";
    return next_timer_in;
}

Sender* SimUtil::getEventSender() {
    return event_sender;
}

void SimUtil::setEventSender(Sender* sender) {
    event_sender = sender;
}

void SimUtil::addTimer(std::string trans_id, int64_t time) {
    scheduled_timers.emplace(std::pair(trans_id, timer_index_counter++), getNetTime() + time);
}

void SimUtil::updateTime() {
    current_time_ms = getSystemTime() - time_at_start; 
}

int SimUtil::getNetTime() {
    return current_time_ms;
}

int64_t SimUtil::getSystemTime() {
    return (std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch())).count();
}

void SimUtil::initializeTime() {
    time_at_start = getSystemTime();
}