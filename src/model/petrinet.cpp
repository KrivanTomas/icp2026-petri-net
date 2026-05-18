/**
 * @file petrinet.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "petrinet.h"
#include <stdexcept>

PetriNet::PetriNet(){
    
}

PetriNet::PetriNet(std::string pnet_name){
    net_name = pnet_name;
}

PetriNet::PetriNet(std::string pnet_name, std::string pnet_comment){
    net_name = pnet_name;
    net_comment = pnet_comment;
}

bool PetriNet::addPlace(const Place& place) {
    if(places.find(place.getId()) != places.end()) {
        return false;
    }
    places.emplace(place.getId(), place);
    return true;
}

bool PetriNet::addTransition(const Transition& transition) {
    if(transitions.find(transition.getId()) != transitions.end()) {
        return false;
    }
    transitions.emplace(transition.getId(), transition);
    return true;
}

bool PetriNet::addArc(const Arc& arc) {
    std::string source_ID = arc.getSourceId();
    std::string target_ID = arc.getTargetId();

    bool source_is_place = places.find(source_ID) != places.end();
    bool source_is_transition = transitions.find(source_ID) != transitions.end();

    bool target_is_place = places.find(target_ID) != places.end();
    bool target_is_transition = transitions.find(target_ID) != transitions.end();

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

    if(arcs.find(arc.getId()) != arcs.end()) {
        return false;
    }

    arcs.emplace(arc.getId(), arc);
    return true;
}

void PetriNet::changePlaceId(std::string old_id, std::string new_id) {
    if(places.find(old_id) == places.end()) {
        throw std::runtime_error("object_doesnt_exist");
    }
    if(new_id == old_id)
    {
        return;
    }
    if(places.find(new_id) != places.end() ||
        transitions.find(new_id) != transitions.end() ||
        arcs.find(new_id) != arcs.end())
    {
        //place with this id already exists
        throw std::runtime_error("id_already_in_use");
    }
    Place p = places.at(old_id);
    p.setId(new_id);
    for(auto pair : arcs) {
        if(pair.second.getSourceId() == old_id) {
            pair.second.setSourceId(new_id);
        }
        if(pair.second.getTargetId() == old_id) {
            pair.second.setTargetId(new_id);
        }
    }
    places.erase(old_id);
    addPlace(p);
}

void PetriNet::changeTransitionId(std::string old_id, std::string new_id) {
    if(transitions.find(old_id) == transitions.end()) {
        throw std::runtime_error("object_doesnt_exist");
    }
    if(new_id == old_id)
    {
        return;
    }
    if(places.find(new_id) != places.end() ||
        transitions.find(new_id) != transitions.end() ||
        arcs.find(new_id) != arcs.end())
    {
        //place with this id already exists
        throw std::runtime_error("id_already_in_use");
    }
    Transition t = transitions.at(old_id);
    t.setId(new_id);
    for(auto pair : arcs) {
        if(pair.second.getSourceId() == old_id) {
            pair.second.setSourceId(new_id);
        }
        if(pair.second.getTargetId() == old_id) {
            pair.second.setTargetId(new_id);
        }
    }
    transitions.erase(old_id);
    addTransition(t);
}

void PetriNet::changeArcId(std::string old_id, std::string new_id) {
    if(arcs.find(old_id) == arcs.end()) {
        throw std::runtime_error("object_doesnt_exist");
    }
    if(new_id == old_id)
    {
        return;
    }
    if(places.find(new_id) != places.end() ||
        transitions.find(new_id) != transitions.end() ||
        arcs.find(new_id) != arcs.end())
    {
        //place with this id already exists
        throw std::runtime_error("id_already_in_use");
    }
    Arc a = arcs.at(old_id);
    a.setId(new_id);
    arcs.erase(old_id);
    addArc(a);
}

void PetriNet::removePlace(std::string place_id) {
    places.erase(place_id);
}

void PetriNet::removeTransition(std::string transition_id) {
    transitions.erase(transition_id);
}

void PetriNet::removeArc(std::string arc_id) {
    arcs.erase(arc_id);
}

std::string PetriNet::getName() const {
    return net_name;
}

void PetriNet::setName(const std::string& name) {
    net_name = name;
}

std::string PetriNet::getComment() const {
    return net_comment;
}

void PetriNet::setComment(const std::string& comment) {
    net_comment = comment;
}

std::string PetriNet::getInputValue(const std::string& input_name) const {
    auto it = internal_inputs.find(input_name);
    if(it != internal_inputs.end()) {
        return it->second;
    }
    return "";
}

void PetriNet::setInputValue(const std::string& input_name, const std::string& value) {
    internal_inputs[input_name] = value;
}

std::map<std::string, std::string> PetriNet::getInputs() {
    return internal_inputs;
}

void PetriNet::clearInputs() {
    internal_inputs.clear();
}

std::string PetriNet::getOutputValue(const std::string& output_name) const {
    auto it = internal_outputs.find(output_name);
    if(it != internal_outputs.end()) {
        return it->second;
    }
    return "";
}

void PetriNet::setOutputValue(const std::string& output_name, const std::string& value) {
    internal_outputs[output_name] = value;
}

std::map<std::string, std::string> PetriNet::getOutputs() {
    return internal_outputs;
}

void PetriNet::clearOutputs() {
    internal_outputs.clear();
}

std::string PetriNet::getVariableValue(const std::string& var_name) const {
    auto it = internal_variables.find(var_name);
    if(it != internal_variables.end()) {
        return it->second;
    }
    return "";
}

std::map<std::string, std::string> PetriNet::getVariables() const {
    return internal_variables;
}


void PetriNet::setVariable(const std::string& var_name, const std::string& value) {
    internal_variables[var_name] = value;
}

void PetriNet::clearVariables() {
    internal_variables.clear();
}

void PetriNet::reset() {
    //reset place tokens
    for(auto& place : places) {
        place.second.setCurrentTokens(place.second.getInitialTokens());
    }
}

void PetriNet::clear() {
    places.clear();
    transitions.clear();
    arcs.clear();
    internal_inputs.clear();
    internal_variables.clear();
    net_name = "Unknown petrinet";
    net_comment = "";
}

bool PetriNet::isInputDefined(const std::string& input_name) const {
    if(internal_inputs.find(input_name) != internal_inputs.end()) {
        return true;
    }
    return false;
}

std::map<std::string, Place>& PetriNet::getPlaces() {
    return places;
}

std::map<std::string, Transition>& PetriNet::getTransitions() {
    return transitions;
}

std::map<std::string, Arc>& PetriNet::getArcs() {
    return arcs;
}
