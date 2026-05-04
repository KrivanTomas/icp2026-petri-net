/**
 * @file place.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "place.h"

Place::Place(const std::string& id, int initial_tokens) : m_id(id), m_initial_tokens(initial_tokens), m_current_tokens(initial_tokens) {}

std::string Place::getId() {
    return m_id;
}

int Place::getInitialTokens() {
    return m_initial_tokens;
}

void Place::setInitialTokens(int count) {
    m_initial_tokens = count;
}

int Place::getCurrentTokens() {
    return m_current_tokens;
}

void Place::setCurrentTokens(int count) {
    m_current_tokens = count;
}

std::string Place::getActionCode() {
    return m_action_code;
}

void Place::setActionCode(const std::string& code) {
    m_action_code = code;
}