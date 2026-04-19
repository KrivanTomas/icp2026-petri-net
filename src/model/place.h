#ifndef PLACE_H
#define PLACE_H

#include <Qstring>
#include <QJsonObject>

/**
* @class Place
* @brief Class that represents a place in Petri net where are tokens
*/
class Place {
public:
    /**
     * @brief Constructor for Place.
     * @param id Identifier of the place.
     * @param tokens Number of tokens (default value is 0).
     */
    Place(QString id, int tokens = 0);
    QString id;
    int tokens;

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
#endif
