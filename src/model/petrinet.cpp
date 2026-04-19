#include "petrinet.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

void PetriNet::addPlace(const Place& plc) {
    places.append(plc);
}

void PetriNet::addTransition(const Transition& tr) {
    transitions.append(tr);
}

bool PetriNet::save(const QString& fileName) const {
    QJsonObject root;
    QJsonArray plcArray, trArray;

    for (const auto& plc : places) {
        plcArray.append(plc.toJson());
    }
    for (const auto& tr : transitions) {
        trArray.append(tr.toJson());
    }

    root["places"] = plcArray;
    root["transitions"] = trArray;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    file.write(QJsonDocument(root).toJson());
    return true;
}

bool PetriNet::load(const QString& fileName){

    QFile file(fileName);
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
}
