/**
 * @file place.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "place.h"

Place::Place(QString id, int token_count) : id(id), token_count(token_count) {}

QJsonObject Place::toJson() const {
    QJsonObject json;
    json["id"] = id;
    json["token_count"] = token_count;
    return json;
}

Place Place::fromJson(const QJsonObject& json) {
    return Place(json["id"].toString(), json["token_count"].toInt());
}
