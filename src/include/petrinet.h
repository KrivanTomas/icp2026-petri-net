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
#include "place.h"
#include "transition.h"
#include "arc.h"

struct PendingTimer {
    std::string transition_id;
    int64_t target_time_ms;
};

/**
 * @class PetriNet
 * @brief Main container of Petri Net components
 */
class PetriNet 
{
public:
    /**
     * @brief Adds a place to the petri net.
     * @param plc The place to add.
     */
    void addPlace(const Place &plc);

    /**
     * @brief Adds a transition to the petri net.
     * @param tr The transition to add.
     */
    void addTransition(const Transition &tr);

    /**
     * @brief Adds an arc to petri net.
     * @param arc The arc to be added.
     */
    void addArcs(const Arc &arc);

    /**
     * @brief Gets the name of PetriNet.
     */
    std::string getName() const;

    /**
     * @brief Sets the name of petri net.
     * @param name New name.
     */
    void setName(std::string& name);
    
    /**
     * @brief Gets network description or comment.
     */
    std::string getComment() const;
    
    /**
     * @brief Sets the network description or comment.
     * @param comment The comment/description.
     */
    void setComment(std::string& comment);

    /**
     * @brief Retrieves last value of external input.
     * @param input_name The identifier of the input.
     * @return The stored value, or an empty string. 
     */
    std::string getInputValue(std::string& input_name) const;

    /**
     * @brief Sets last known value of an external input.
     * @param input_name The identifier of the input.
     * @param value New value.
     */
    void setInputValue(std::string& input_name, std::string& value);

    /**
     * @brief Retrieves the value of an internal network variable.
     * @param var_name Name of the variable.
     * @return The stored value, or an emty string.
     */
    std::string getVariable(std::string& var_name) const;

    /**
     * @brief Sets the value of an internal network variable.
     * @param var_name Name of the variable.
     * @param value New value.
     */
    void setvariable(std::string& var_name, std::string& value);

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
    void runMicroSteps();

    /**
     * @brief Checks for timers to expire, and fires them if necessary.
     * @param current_time_ms Current system time in milliseconds.
     */
    void updateTime(int64_t current_time_ms);

    //getters
    std::map<std::string, Place>& getPlaces();
    std::map<std::string, Transition>& getTransitions();
    std::map<std::string, Arc>& getArcs();

private:
    std::string m_name;
    std::string m_comment;

    std::map<std::string, std::string> m_inputs;
    std::map<std::string, std::string> m_variables;

    std::map<std::string, Place> m_places;
    std::map<std::string, Transition> m_transitions;
    std::map<std::string, Arc> m_arcs;

    int64_t m_current_time_ms = 0;
    std::vector<PendingTimer> m_timers;
};
