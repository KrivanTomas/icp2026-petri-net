/**
 * @file arc.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "arc.h"

Arc::Arc(const std::string& id, const std::string& source_id, const std::string& target_id, int weight) : m_id(id), m_source_id(source_id), m_target_id(target_id), m_weight(weight){}

std::string Arc::getId() {
    return m_id;
}

std::string Arc::getSourceId() {
    return m_source_id;
}

std::string Arc::getTargetId() {
    return m_target_id;
}

int Arc::getWeight() {
    return m_weight;
}

void Arc::setWeight(int weight) {
    m_weight = weight;
}