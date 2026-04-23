/**
 * @file place.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "place.h"

Place::Place(const QString& id, int initial_tokens) : m_id(id), m_initial_tokens(initial_tokens), m_current_tokens(initial_tokens) {}

QString Place::getId(){
    return m_id;
}

int Place::getInitialTokens(){
    return m_initial_tokens;
}

void Place::setInitialTokens(int count){
    m_initial_tokens = count;
}

int Place::getCurrentTokens(){
    return m_current_tokens;
}

void Place::setCurrentTokens(int count){
    m_current_tokens = count;
}

QString Place::getActionCode(){
    return m_action_code;
}

void Place::setActionCode(const QString& code){
    m_action_code = code;
}

QJsonObject Place::toJson() const {
    QJsonObject json;
    json["id"] = m_id;
    json["initial_tokens"] = m_initial_tokens;
    json["current_tokens"] = m_current_tokens;
    json["action_code"] = m_action_code;
    return json;
}

Place Place::fromJson(const QJsonObject& json) {
    Place place(json["id"].toString(), json["initial_tokens"].toInt(0));
    place.setCurrentTokens(json["current_tokens"].toInt(place.getInitialTokens()));
    place.setActionCode(json["action_code"].toString());
    return place;
}
