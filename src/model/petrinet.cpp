/**
 * @file petrinet.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "petrinet.h"

bool PetriNet::addPlace(const Place& place) {
    if(m_places.find(place.getId()) != m_places.end()) {
        return false;
    }
    m_places.emplace(place.getId(), place);
    return true;
}

bool PetriNet::addTransition(const Transition& transition) {
    if(m_transitions.find(transition.getId()) != m_transitions.end()) {
        return false;
    }
    m_transitions.emplace(transition.getId(), transition);
    return true;
}

bool PetriNet::addArcs(const Arc& arc) {
    std::string source_ID = arc.getSourceId();
    std::string target_ID = arc.getTargetId();

    bool source_is_place = m_places.find(source_ID) != m_places.end();
    bool source_is_transition = m_transitions.find(source_ID) != m_transitions.end();

    bool target_is_place = m_places.find(target_ID) != m_places.end();
    bool target_is_transition = m_transitions.find(target_ID) != m_transitions.end();

    if(!(source_is_place || source_is_transition)) {
        return false;
    }

    if(!(target_is_place || target_is_transition)) {
        return false;
    }

    if(source_is_place && target_is_place) {
        return false;
    }

    if(source_is_transition && target_is_transition) {
        return false;
    }

    if(m_arcs.find(arc.getId()) != m_arcs.end()) {
        return false;
    }

    m_arcs.emplace(arc.getId(), arc);
    return true;
}

std::string PetriNet::getName() const {
    return m_name;
}

void PetriNet::setName(std::string& name) {
    m_name = name;
}

std::string PetriNet::getComment() const {
    return m_comment;
}

void PetriNet::setComment(std::string& comment) {
    m_comment = comment;
}

std::string PetriNet::getInputValue(std::string& input_name) const {
    auto it = m_inputs.find(input_name);
    if(it != m_inputs.end()) {
        return it->second;
    }
    return "";
}

void PetriNet::setInputValue(std::string& input_name, std::string& value) {
    m_inputs[input_name] = value;
    m_defined_inputs.insert(input_name);
}

std::string PetriNet::getVariable(std::string& var_name) const {
    auto it = m_variables.find(var_name);
    if(it != m_variables.end()) {
        return it->second;
    }
    return "";
}

void PetriNet::setvariable(std::string& var_name, std::string& value) {
    m_variables[var_name] = value;
}

bool PetriNet::ableToBeFired(const std::string& transition_id) {
    //check if transition with this ID exists
    if(m_transitions.find(transition_id) == m_transitions.end()) {
        return false;
    }

    std::string required_event = m_transitions.at(transition_id).getInputEventName();
    if(!required_event.empty() && required_event != m_event) {
        return false;
    }

    for(auto& pair : m_arcs) {
        auto& arc = pair.second;
        //if arc points into this transition
        if(arc.getTargetId() == transition_id) {
            std::string place_source_id = arc.getSourceId();
            int requiredTokens = arc.getWeight();
            
            //finding of the entry point and checking tokens
            bool enough_tokens = false;

            //
            if(auto place = m_places.find(place_source_id); place != m_places.end()){
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

bool PetriNet::fire(const std::string& transition_id) {
    if(!ableToBeFired(transition_id)) {
        return false;
    }

    //removing tokens
    for(auto& pair : m_arcs) {
        auto& arc = pair.second;
        if(arc.getTargetId() == transition_id) {
            std::string place_source_id = arc.getSourceId();
            int tokens_remove = arc.getWeight();

            
            if(auto place = m_places.find(place_source_id); place != m_places.end()) {
                place->second.setCurrentTokens(place->second.getCurrentTokens() - tokens_remove);
                place->second.setLasttimeChange(m_current_time_ms);
            }
        }
    }

    //adding of tokens
    for(auto& pair : m_arcs) {
        auto& arc = pair.second;
        //if arc exits out of this transition, then it is an exit arc
        if(arc.getSourceId() == transition_id) {
            std::string place_target_id = arc.getTargetId();
            int tokens_add = arc.getWeight();
            
            if(auto place = m_places.find(place_target_id); place != m_places.end()) {
                place->second.setCurrentTokens(place->second.getCurrentTokens() + tokens_add);
                place->second.setLasttimeChange(m_current_time_ms);
            }
        }
    }
    return true;
}

//setting initial value of tokens for every place
void PetriNet::reset() {
    for(auto& place : m_places) {
        place.second.setCurrentTokens(place.second.getInitialTokens());
    }
}

void PetriNet::runMicroSteps() {
    bool network_change = true;

    while(network_change) {
        network_change = false;
        for(auto& pair : m_transitions) {
            auto& trans = pair.second;
            std::string trans_id = trans.getId();

            if(ableToBeFired(trans_id)) {
                if(trans.getDelay() > 0) {
                    bool timer_exists = false;
                    for(auto& timer : m_timers) {
                        if(timer.transition_id == trans_id) {
                            timer_exists = true;
                            break;
                        }
                    }
                    if(!timer_exists) {
                        PendingTimer new_timer;
                        new_timer.transition_id = trans_id;
                        new_timer.target_time_ms = m_current_time_ms + trans.getDelay();
                        m_timers.push_back(new_timer);
                    }
                }
                else {
                    if(fire(trans_id)) {
                        network_change = true;
                    }
                }
                
            }
        }
    }
}

void PetriNet::updateTime(int64_t current_time_ms) {
    m_current_time_ms = current_time_ms;
    bool timer_fired = false;

    for(auto it = m_timers.begin(); it != m_timers.end(); ) {
        if(m_current_time_ms >= it->target_time_ms) {
            std::string t_id = it->transition_id;
            if(ableToBeFired(t_id)) {
                fire(t_id);
                timer_fired = true;
            }
            it = m_timers.erase(it);
        }
        else {
            it++;
        }
    } 
    if(timer_fired) {
        runMicroSteps();
    }
}

int PetriNet::petriNetInternalTime() {
    return m_current_time_ms;
}

bool PetriNet::isDefined(const std::string& input_name) {
    if(m_defined_inputs.find(input_name) != m_defined_inputs.end()) {
        return true;
    }
    return false;
}

void PetriNet::triggerEvent(const std::string& event) {
    m_event = event;
    runMicroSteps();
    m_event = "";
}

std::map<std::string, Place>& PetriNet::getPlaces() {
    return m_places;
}

std::map<std::string, Transition>& PetriNet::getTransitions() {
    return m_transitions;
}

std::map<std::string, Arc>& PetriNet::getArcs() {
    return m_arcs;
}