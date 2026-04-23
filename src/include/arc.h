/**
 * @file arc.h
 *
 * @brief Header file for arcs
 *
 * @author
 *     Tomáš Kudera
 */
#pragma once

#include <QString>
#include <QJsonObject>

/**
 * @class Arc
 * @brief Třída pro reprezentaci orientovaných hran v petriho síti
 * 
 * propojení míst a přechodů 
 */
class Arc
{
public:
    /**
     * @brief Constructor of an Arc.
     * @param id Unique identifier of arc.
     * @param source_id The identifier of the source node.
     * @param target_id The identifier of the target node.
     * @param weight The weight of the arc.
     */
    Arc(const QString& id, const QString& source_id, const QString& target_id, int weight = 1);

    /**
     * @brief Gets the unique identifier of the arc.
     */
    QString getId();

    /**
     * @brief Gets the unique identifier of the source node.
     */
    QString getSourceId();

    /**
     * @brief Gets the unique identifier of the target node.
     */
    QString getTargetId();

    /**
     * @brief Gets the weight of the arc.
     */
    int getWeight();

    /**
     * @brief Sets new weight for the arc.
     * @param weight New value of the weight.
     */
    void setWeight(int weight);

    /**
     * @brief Serializes the data of the arc to JSON format.
     * @return QJsonObject representing the arc.
     */
    QJsonObject toJson();

    /**
     * @brief Deserialization of data of the arc.
     * @param json Object containing JSON data.
     * @return New instance of the arc. 
     */
    static Arc fromJson(const QJsonObject& json);

private:
    QString m_id;
    QString m_source_id;
    QString m_target_id;
    int m_weight;
};