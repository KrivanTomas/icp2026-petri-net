/**
 * @file transition.h
 *
 * @brief Header file for transitions
 *
 * @author
 *     Tomáš Kudera
 */


#pragma once

#include <QString>
#include <QJsonObject>

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
    Transition(const QString& id);
    
    /**
     * @brief Gets unique identifier of the transition.
     */
    QString getId();

    /**
     * @brief Gets the name of the input event.
     */
    QString getInputEventName();

    /**
     * @brief Sets the name of external event.
     * @param event_name The event name.
     */
    void setInputEventName(const QString& event_name);

    /**
     * @brief Gets guard condition.
     */
    QString getGuardcondition();

    /**
     * @brief Sets boolean expression/condition.
     * @param condition An expression.
     */
    void setGuardCondition(const QString& condition);

    /**
     * @brief Gets time delay (firing).
     */
    int getDelay();

    /**
     * @brief Sets new time delay for firing.
     * @param delay Delay in miliseconds.
     */
    void setDelay(int delay_in_ms);

    /**
     * @brief gets the action code executed by this transition.
     */
    QString getActionCode();

    /**
     * @brief Sets the action code (inscription language).
     * @param action_code Source code of the action.
     */
    void setActionCode(const QString& action_code);

    /**
     * @brief Serializes the transition into JSON object.
     * @return QJsonObject representing transition.
     */
    QJsonObject toJson() const;

    /**
     * @brief Creates an instance of Transition from JSON data.
     * @param json Object with "id".
     * @return A new Transition object.
     */
    static Transition fromJson(const QJsonObject& json);

private:
    QString m_id;
    QString m_input_event_name;
    QString m_guard_condition;
    int m_delay_ms;
    QString m_action_code;
};
