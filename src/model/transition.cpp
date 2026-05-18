/**
 * @file transition.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "transition.h"

Transition::Transition(const std::string& id) : id(id), delay_ms(0), enabled(true) {}

std::string Transition::getId() const {
    return id;
}

void Transition::setId(std::string new_id) {
    id = new_id;
}

std::string Transition::getInputEventName() const {
    return input_event_name;
}

void Transition::setInputEventName(const std::string& event_name) {
    input_event_name = event_name;
}

std::string Transition::getGuardCondition() const {
    return guard_condition;
}

void Transition::setGuardCondition(const std::string& condition) {
    guard_condition = condition;
}

int64_t Transition::getDelay() const {
    return delay_ms;
}

void Transition::setDelay(int64_t delay_in_ms) {
    delay_ms = delay_in_ms;
}

std::string Transition::getActionCode() const {
    return action_code;
}

void Transition::setActionCode(const std::string& action_code) {
    this->action_code = action_code;
}

bool Transition::isEnabled() const {
    return enabled;
}

void Transition::setEnabled(bool set_enabled) {
    enabled = set_enabled;
}
