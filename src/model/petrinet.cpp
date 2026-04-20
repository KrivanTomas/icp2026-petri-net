/**
 * @file petrinet.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "petrinet.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

void PetriNet::addPlace(const Place& place) {
    places.append(place);
}

void PetriNet::addTransition(const Transition& transition) {
    transitions.append(transition);
}

bool PetriNet::save(const QString& file_name) const {
    QJsonObject root;
    QJsonArray place_array, transition_array;

    for (const auto& place : places) {
        place_array.append(place.toJson());
    }
    for (const auto& transition : transitions) {
        transition_array.append(transition.toJson());
    }

    root["places"] = place_array;
    root["transitions"] = transition_array;

    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(QJsonDocument(root).toJson());
    return true;
}

bool PetriNet::load(const QString& file_name){

    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();

    places.clear();
    transitions.clear();

    for (auto v : root["places"].toArray()) {
        places.append(Place::fromJson(v.toObject()));
    }
    for (auto v : root["transitions"].toArray()) {
        transitions.append(Transition::fromJson(v.toObject()));
    }

    return true;
}
