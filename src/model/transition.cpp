#include "transition.h"

Transition::Transition(QString id) : id(id) {}

QJsonObject Transition::toJson() const {
    QJsonObject json;
    json["id"] = id;
    return json;
}

Transition Transition::fromJson(const QJsonObject& json) {
    return Transition(json["id"].toString());
}
