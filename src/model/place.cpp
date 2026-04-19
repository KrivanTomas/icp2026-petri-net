#include "place.h"

Place::Place(QString id, int tokens) : id(id), tokens(tokens) {}

QJsonObject Place::toJson() const {
    QJsonObject json;
    json["id"] = id;
    json["token"] = tokens;
    return json;
}

Place Place::fromJson(const QJsonObject& json) {
    return Place(json["id"].toString(), json["tokens"].toInt());
}
