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

std::string Arc::getSourceId() const {
    return source_id;
}

std::string Arc::getTargetId() const {
    return target_id;
}

int Arc::getWeight() const {
    return weight;
}

void Arc::setWeight(int weight) {
    weight = weight;
}