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
     * @brief Changed the id (but not in petrinet!)
     */
    void setId(std::string new_id);

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
    int64_t getDelay() const;

    /**
     * @brief Sets new time delay for firing.
     * @param delay Delay in miliseconds.
     */
    void setDelay(int64_t delay_in_ms);

    /**
     * @brief gets the action code executed by this transition.
     */
    std::string getActionCode() const;

    /**
     * @brief Sets the action code (inscription language).
     * @param action_code Source code of the action.
     */
    void setActionCode(const std::string& action_code);

    /**
     * @brief gets the enabled state.
     */
    bool isEnabled() const;

    /**
     * @brief Sets the state of the transition to enabled or not enabled.
     * @param enabled Boolean value to set.
     */
    void setEnabled(bool enabled);

        /**
     * @brief Set the 2D position
     * @param x X-axis position
     * @param y Y-axis position
     */
    void setPosition(float x, float y);

    /**
     * @brief Set the X-axis position
     * @param x value
     */
    void setPosX(float x);

    /**
     * @brief Set the Y-axis position
     * @param y value
     */
    void setPosY(float y);

    /**
     * @brief Get the 2D position
     * @return Pair containing x and y coordinates.
     */
    std::pair<float, float> getPosition();

private:
    std::string id;
    std::string input_event_name;
    std::string guard_condition;
    int delay_ms;
    std::string action_code;
    bool enabled;
    std::pair<float, float> gui_position;
};
