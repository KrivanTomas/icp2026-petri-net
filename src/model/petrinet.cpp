/**
 * @file petrinet.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "petrinet.h"

PetriNet::PetriNet(){
    time_at_start = getCurrentTime();
}

PetriNet::PetriNet(std::string pnet_name){
    time_at_start = getCurrentTime();
    m_name = pnet_name;
}

PetriNet::PetriNet(std::string pnet_name, std::string pnet_comment){
    time_at_start = getCurrentTime();
    m_name = pnet_name;
    m_comment = pnet_comment;
}

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

void PetriNet::setName(const std::string& name) {
    m_name = name;
}

std::string PetriNet::getComment() const {
    return m_comment;
}

void PetriNet::setComment(const std::string& comment) {
    m_comment = comment;
}

std::string PetriNet::getInputValue(const std::string& input_name) const {
    auto it = m_inputs.find(input_name);
    if(it != m_inputs.end()) {
        return it->second;
    }
    return "";
}

void PetriNet::setInputValue(const std::string& input_name, const std::string& value) {
    m_inputs[input_name] = value;
}

std::string PetriNet::getVariable(const std::string& var_name) const {
    auto it = m_variables.find(var_name);
    if(it != m_variables.end()) {
        return it->second;
    }
    return "";
}

void PetriNet::setVariable(const std::string& var_name, const std::string& value) {
    m_variables[var_name] = value;
}

bool PetriNet::ableToBeFired(const std::string& transition_id) {
    //check if transition with this ID exists
    if(m_transitions.find(transition_id) == m_transitions.end()) {
        return false;
    }
    if(!m_transitions.at(transition_id).isEnabled()) {
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
                place->second.setLastTimeChange(m_current_time_ms);
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
                place->second.setLastTimeChange(m_current_time_ms);
            }
        }
    }
    return true;
}

//setting initial value of tokens for every place
void PetriNet::reset() {
    //reset place tokens
    for(auto& place : m_places) {
        place.second.setCurrentTokens(place.second.getInitialTokens());
    }
    //reset 
    time_at_start = getCurrentTime();
}

void PetriNet::fireScheduledTransitions() {
    bool network_change = true;

    while(network_change) {
        network_change = false;
        for(auto& pair : m_timers) {
            Transition trans = m_transitions.at(pair.first);
            std::string trans_id = pair.first;

            if(trans.getDelay() <= 0 && trans.isEnabled()) {

                if(fire(trans_id)) {
                    // another transition MAY be able to fire now
                    network_change = true;

                }
                //remove the timer from scheduled timers even if it was not enabled
                m_timers.erase(trans_id);
            }
        }
    }
}

void PetriNet::updateTime() {
    m_current_time_ms = getCurrentTime() - time_at_start; 
}

int PetriNet::petriNetInternalTime() const {
    return m_current_time_ms;
}

int64_t PetriNet::getCurrentTime() const {
    return (std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch())).count();
}

bool PetriNet::isInputDefined(const std::string& input_name) const {
    if(m_inputs.find(input_name) != m_inputs.end()) {
        return true;
    }
    return false;
}

const std::map<std::string, Place>& PetriNet::getPlaces() const {
    return m_places;
}

const std::map<std::string, Transition>& PetriNet::getTransitions() const {
    return m_transitions;
}

const std::map<std::string, Arc>& PetriNet::getArcs() const {
    return m_arcs;
}