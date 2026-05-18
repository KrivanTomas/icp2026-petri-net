/**
 * @file petrinet.h
 *
 * @brief Header file for petri net containing class
 *
 * @author
 *     Tomáš Kudera
 */


#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>
#include <chrono>
#include "place.h"
#include "transition.h"
#include "arc.h"

class SimUtil;

/**
 * @class PetriNet
 * @brief Main container of Petri Net components
 */
class PetriNet 
{
    friend class SimUtil;
public:
    /**
     * @brief petrinet constructor and initializer
     */
    PetriNet();
    /**
     * @brief petrinet constructor and initializer
     * @param pnet_name Name of the petrinet
     */
    PetriNet(std::string pnet_name);
    /**
     * @brief petrinet constructor and initializer
     * @param pnet_name Name of the petrinet
     * @param pnet_comment Comment of the petrinet
     */
    PetriNet(std::string pnet_name, std::string pnet_comment);

    /**
     * @brief Adds a place to the petri net.
     * @param plc The place to add.
     * @return true if place was added, or else false
     */
    bool addPlace(const Place &plc);

    /**
     * @brief Adds a transition to the petri net.
     * @param tr The transition to add.
     * @return true if transition was added, or false
     */
    bool addTransition(const Transition &tr);

    /**
     * @brief Adds an arc to petri net.
     * @param arc The arc to be added.
     * @return true if an arc was added, else false
     */
    bool addArc(const Arc &arc);

    /**
     * @brief Changes the id of a place in this petrinet
     * @param old_id Id of the current place
     * @param new_id New id to replace the current one
     * @throw <id_already_in_use> if new_id is already in use
     */
    void changePlaceId(std::string old_id, std::string new_id);

    /**
     * @brief Changes the id of a transition in this petrinet
     * @param old_id Id of the current transition
     * @param new_id New id to replace the current one
     * @throw <id_already_in_use> if new_id is already in use
     */
    void changeTransitionId(std::string old_id, std::string new_id);

    /**
     * @brief Changes the id of an arc in this petrinet
     * @param old_id Id of the current arc
     * @param new_id New id to replace the current one
     * @throw <id_already_in_use> if new_id is already in use
     */
    void changeArcId(std::string old_id, std::string new_id);

    /** 
     * @brief Removes a place from this petrinet
     * @param place_id Id of the place
    */
    void removePlace(std::string place_id);

    /** 
     * @brief Removes a transition from this petrinet
     * @param transition_id Id of the transition
    */
    void removeTransition(std::string transition_id);

    /** 
     * @brief Removes an arc from this petrinet
     * @param place_id Id of the arc
    */
    void removeArc(std::string arc_id);
    /**
     * @brief Gets the name of PetriNet.
     * @return Name of the PetriNet.
     */
    std::string getName() const;

    /**
     * @brief Sets the name of petri net.
     * @param name New name.
     */
    void setName(const std::string& name);
    
    /**
     * @brief Gets network description or comment.
     * @return Network description or comment.
     */
    std::string getComment() const;
    
    /**
     * @brief Sets the network description or comment.
     * @param comment The comment/description.
     */
    void setComment(const std::string& comment);

    /**
     * @brief Retrieves last value of internal input.
     * @param input_name The identifier of the input.
     * @return The stored value, or an empty string. 
     */
    std::string getInputValue(const std::string& input_name) const;

    /**
     * @brief Sets last known value of an internal input. Creates a new one if it doesnt yet exist.
     * @param input_name The identifier of the input.
     * @param value New value.
     */
    void setInputValue(const std::string& input_name, const std::string& value);

    /**
     * @brief Gets the internal_inputs map
     * @return map of the inputs
     */
    std::map<std::string, std::string> getInputs();

    /**
     * @brief Clears the internal_inputs map
     */
    void clearInputs();

    /**
     * @brief Retrieves last value of internal output.
     * @param output_name The identifier of the output.
     * @return The stored value, or an empty string. 
     */
    std::string getOutputValue(const std::string& output_name) const;

    /**
     * @brief Sets value of an internal output. Creates a new one if it doesnt yet exist.
     * @param output_name The identifier of the output.
     * @param value New value.
     */
    void setOutputValue(const std::string& output_name, const std::string& value);

    /**
     * @brief Gets the internal_outputs map
     * @return map of the outputs
     */
    std::map<std::string, std::string> getOutputs();

    /**
     * @brief Clears the internal_outputs map
     */
    void clearOutputs();

    /**
     * @brief Retrieves the value of an internal network variable.
     * @param var_name Name of the variable.
     * @return The stored value, or an emty string.
     */
    std::string getVariableValue(const std::string& var_name) const;

    /**
     * @brief Gets the internal_variables map
     * @return The whole map
     */
    std::map<std::string, std::string> getVariables() const;

    /**
     * @brief Sets the value of an internal network variable. Creates a new one if it doesnt yet exist.
     * @param var_name Name of the variable.
     * @param value New value.
     */
    void setVariable(const std::string& var_name, const std::string& value);

    /**
     * @brief Clears the internal_variables map
     */
    void clearVariables();

    /**
     * @brief Resets the network into initial state.
     */
    void reset();

    /**
     * @brief Clear the whole network
     */
    void clear();

    /**
     * @brief Check if external input is defined.
     * @param input_name Validated input.
     * @return True if input is defined, or else false.
     */
    bool isInputDefined(const std::string& input_name) const;

    //getters
    std::map<std::string, Place>& getPlaces();
    std::map<std::string, Transition>& getTransitions();
    std::map<std::string, Arc>& getArcs();

private:
    std::string net_name = "Unknown petrinet";
    std::string net_comment = "";

    std::map<std::string, std::string> internal_inputs;
    std::map<std::string, std::string> internal_outputs;
    std::map<std::string, std::string> internal_variables;

    std::map<std::string, Place> places;
    std::map<std::string, Transition> transitions;
    std::map<std::string, Arc> arcs;
};
