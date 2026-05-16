/**
 * @file transition.h
 *
 * @brief Header file for transitions
 *
 * @author
 *     Tomáš Kudera
 */


#pragma once

#include <string>

/**
 * @class Transition
 * @brief Transition element in the Petri Net.
 */
class Transition 
{
public:
    /**
     * @brief Constructor for a Transition.
     * @param id Identifier.
     */
    Transition(const std::string& id);
    
    /**
     * @brief Gets unique identifier of the transition.
     */
    std::string getId() const;

    /**
     * @brief Gets the name of the input event.
     */
    std::string getInputEventName() const;

    /**
     * @brief Sets the name of external event.
     * @param event_name The event name.
     */
    void setInputEventName(const std::string& event_name);

    /**
     * @brief Gets guard condition.
     */
    std::string getGuardCondition() const;

    /**
     * @brief Sets boolean expression/condition.
     * @param condition An expression.
     */
    void setGuardCondition(const std::string& condition);

    /**
     * @brief Gets time delay (firing).
     */
    int getDelay() const;

    /**
     * @brief Sets new time delay for firing.
     * @param delay Delay in miliseconds.
     */
    void setDelay(int delay_in_ms);

    /**
     * @brief gets the action code executed by this transition.
     */
    std::string getActionCode() const;

    /**
     * @brief Sets the action code (inscription language).
     * @param action_code Source code of the action.
     */
    void setActionCode(const std::string& action_code);

private:
    std::string m_id;
    std::string m_input_event_name;
    std::string m_guard_condition;
    int m_delay_ms;
    std::string m_action_code;
};
