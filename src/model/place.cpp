/**
 * @file place.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "place.h"

Place::Place(const std::string& id, int initial_tokens) : id(id), initial_tokens(initial_tokens), current_tokens(initial_tokens) {}

std::string Place::getId() const {
    return id;
}

void Place::setId(std::string new_id) {
    id = new_id;
}

int Place::getInitialTokens() const {
    return initial_tokens;
}

void Place::setInitialTokens(int count) {
    initial_tokens = count;
}

int Place::getCurrentTokens() const {
    return current_tokens;
}

void Place::setCurrentTokens(int count) {
    current_tokens = count;
}

std::string Place::getActionCode() const {
    return action_code;
}

void Place::setActionCode(const std::string& code) {
    action_code = code;
}

int Place::getLastTimeChange() const {
    return last_change_time_ms;
}

void Place::setLastTimeChange(int64_t time_ms) {
    last_change_time_ms = time_ms;
}

void Place::setPosition(float x, float y) {
    gui_position.first = x;
    gui_position.second = y;
}

void Place::setPosX(float x) {
    gui_position.first = x;
}

void Place::setPosY(float y) {
    gui_position.second = y;
}

std::pair<float, float> Place::getPosition() const {
    return gui_position;
}