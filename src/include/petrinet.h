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
#include "event.h"



/**
 * @class PetriNet
 * @brief Main container of Petri Net components
 */
class PetriNet
{
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
    bool addArcs(const Arc &arc);

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
     * @brief Retrieves last value of external input.
     * @param input_name The identifier of the input.
     * @return The stored value, or an empty string. 
     */
    std::string getInputValue(const std::string& input_name) const;

    /**
     * @brief Sets last known value of an external input.
     * @param input_name The identifier of the input.
     * @param value New value.
     */
    void setInputValue(const std::string& input_name, const std::string& value);

    /**
     * @brief Retrieves the value of an internal network variable.
     * @param var_name Name of the variable.
     * @return The stored value, or an emty string.
     */
    std::string getVariable(const std::string& var_name) const;

    /**
     * @brief Sets the value of an internal network variable.
     * @param var_name Name of the variable.
     * @param value New value.
     */
    void setVariable(const std::string& var_name, const std::string& value);

    /**
     * @brief Function checks if transition has enough tokens to be fired.
     * @param transition_id ID of transition, that is checked.
     * @return True, if transition can be fired, or false if can not.
     */
    bool ableToBeFired(const std::string& transition_id);

    /**
     * @brief Function provides transition firing
     * @param transition_id ID of transition.
     * @return True if transition was safely fired, else false.
     */
    bool fire(const std::string& transition_id);

    /**
     * @brief Resets the network into initial state.
     */
    void reset();

    /**
     * @brief Main simulation loop. Performs the maximum number of independent firings 
     * and stabilizes the network (microsteps). Handles only instantaneous transitions. 
     */
    void fireScheduledTransitions();

    /**
     * @brief Updates internal time. (Milliseconds since launch).
     */
    void updateTime();

    /**
     * @brief Returns current time of the petri net.
     * @return Time in milliseconds.
     */
    int petriNetInternalTime() const;

    /**
     * @brief Returns current system time.
     * @return Time in milliseconds.
     */
    int64_t getCurrentTime() const;

    /**
     * @brief Check if external input is defined.
     * @param input_name Validated input.
     * @return True if input is defined, or else false.
     */
    bool isInputDefined(const std::string& input_name) const;

    //getters
    const std::map<std::string, Place>& getPlaces() const;
    const std::map<std::string, Transition>& getTransitions() const;
    const std::map<std::string, Arc>& getArcs() const;

private:
    std::string net_name = "Unknown petrinet";
    std::string net_comment = "";

    std::map<std::string, std::string> internal_inputs;
    std::map<std::string, std::string> internal_variables;

    std::map<std::string, Place> places;
    std::map<std::string, Transition> transitions;
    std::map<std::string, Arc> arcs;

    int64_t time_at_start = 0;
    int64_t current_time_ms = 0;
    std::map<std::string, int64_t> scheduled_timers;
};
