#ifndef TRANSITION_H
#define TRANSITION_H

#include <QString>
#include <QJsonObject>

/**
 * @class Transition
 * @brief Transition element in the Ptri Net.
 */
class Transition {
public:
    /**
     * @brief Constructor for a Transition.
     * @param id Identifier.
     */
    Transition(QString id);
    QString id;

    /**
     * @brief Serializes the transition into JSON object.
     * @return QJsonObject representing transition.
     */
    QJsonObject toJson() const;

    /**
     * @brief Creates an instance of Transition from JSON data.
     * @param json Object with "id".
     * @return A new Transition object.
     */
    static Transition fromJson(const QJsonObject& json);
};

#endif
