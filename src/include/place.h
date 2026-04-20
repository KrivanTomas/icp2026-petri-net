/**
 * @file place.h
 *
 * @brief Header file for places
 *
 * @author
 *     Tomáš Kudera
 */


#pragma once

#include <QString>
#include <QJsonObject>

/**
* @class Place
* @brief Class that represents a place in Petri net where are tokens
*/
class Place
{
public:
    QString id;
    int token_count;

    /**
     * @brief Constructor for Place.
     * @param id Identifier of the place.
     * @param token_count Number of tokens (default value is 0).
     */
    Place(QString id, int token_count = 0);

    /**
     * @brief Searialization of a place for a JSON object
     * @return QjsonObject representing the place
     */
    QJsonObject toJson() const;

    /**
     * @brief Place instance from JSON data
     * @param json Source object
     * @return A place object
     */
    static Place fromJson(const QJsonObject& json);
};
