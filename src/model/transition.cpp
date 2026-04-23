/**
 * @file transition.cpp
 *
 * @author
 *     Tomáš Kudera
 */


#include "transition.h"

Transition::Transition(const QString& id) : m_id(id), m_delay_ms(0) {}

QString Transition::getId(){
    return m_id;
}

QString Transition::getInputEventName(){
    return m_input_event_name;
}
    
void Transition::setInputEventName(const QString& event_name){
    m_input_event_name = event_name;
}

QString Transition::getGuardcondition(){
    return m_guard_condition;
}
    
void Transition::setGuardCondition(const QString& condition){
    m_guard_condition = condition;
}

int Transition::getDelay(){
    return m_delay_ms;
}
    
void Transition::setDelay(int delay_in_ms){
    m_delay_ms = delay_in_ms;
}

QString Transition::getActionCode(){
    return m_action_code;
}
    
void Transition::setActionCode(const QString& action_code){
    m_action_code = action_code;
}

QJsonObject Transition::toJson() const {
    QJsonObject json;
    QJsonObject conditions;
    json["id"] = m_id;
    json["input_event_name"] = m_input_event_name;
    json["guard_condition"] = m_guard_condition;
    json["delay_ms"] = m_delay_ms;
    json["enable_condition"] = conditions;
    json["action_code"] = m_action_code;
    return json;
}

Transition Transition::fromJson(const QJsonObject& json) {
    Transition trans(json["id"].toString());

    if(json.contains("enable_condition")){
        QJsonObject conditions = json["enable_condition"].toObject();
        trans.setInputEventName(conditions["input_event_name"].toString());
        trans.setGuardCondition(conditions["guard_condition"].toString());
        trans.setDelay(conditions["delay_ms"].toInt(0));
    }
    trans.setActionCode(json["action_code"].toString());
    return trans;
}
