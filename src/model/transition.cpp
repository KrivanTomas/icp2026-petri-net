/**
 * @file transition.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "transition.h"

Transition::Transition(const std::string& id) : m_id(id), m_delay_ms(0) {}

std::string Transition::getId() const {
    return m_id;
}

std::string Transition::getInputEventName() const {
    return m_input_event_name;
}
    
void Transition::setInputEventName(const std::string& event_name) {
    m_input_event_name = event_name;
}

std::string Transition::getGuardCondition() const {
    return m_guard_condition;
}
    
void Transition::setGuardCondition(const std::string& condition) {
    m_guard_condition = condition;
}

int Transition::getDelay() const {
    return m_delay_ms;
}
    
void Transition::setDelay(int delay_in_ms) {
    m_delay_ms = delay_in_ms;
}

std::string Transition::getActionCode() const {
    return m_action_code;
}
    
void Transition::setActionCode(const std::string& action_code) {
    m_action_code = action_code;
}