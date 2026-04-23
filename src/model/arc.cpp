/**
 * @file arc.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "arc.h"

Arc::Arc(const QString& id, const QString& source_id, const QString& target_id, int weight) : m_id(id), m_source_id(source_id), m_target_id(target_id), m_weight(weight){}

QString Arc::getId(){
    return m_id;
}

QString Arc::getSourceId(){
    return m_source_id;
}

QString Arc::getTargetId(){
    return m_target_id;
}

int Arc::getWeight(){
    return m_weight;
}

void Arc::setWeight(int weight){
    m_weight = weight;
}

QJsonObject Arc::toJson(){
    QJsonObject json;
    json["id"] = m_id;
    json["source_id"] = m_source_id;
    json["target_id"] = m_target_id;
    json["weight"] = m_weight;
    return json;
}

Arc Arc::fromJson(const QJsonObject& json){
    return Arc(json["id"].toString(), json["source_id"].toString(), json["target_id"].toString(), json["weight"].toInt(1));
}