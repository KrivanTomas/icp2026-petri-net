/**
 * @file arc.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "arc.h"

Arc::Arc(const std::string& id, const std::string& source_id, const std::string& target_id, int weight) : 
    id(id), source_id(source_id), target_id(target_id), weight(weight){}

std::string Arc::getId() const {
    return id;
}

void Arc::setId(std::string new_id) {
    id = new_id;
}

std::string Arc::getSourceId() const {
    return source_id;
}

void Arc::setSourceId(std::string new_id) {
    source_id = new_id;
}

std::string Arc::getTargetId() const {
    return target_id;
}

void Arc::setTargetId(std::string new_id) {
    target_id = new_id;
}

int Arc::getWeight() const {
    return weight;
}

void Arc::setWeight(int weight) {
    this->weight = weight;
}
