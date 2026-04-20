/**
 * @file petrinet.h
 *
 * @brief Header file for petri net containing class
 *
 * @author
 *     Tomáš Kudera
 */


#pragma once

#include <QList>
#include <QString>
#include "place.h"
#include "transition.h"

/**
 * @class PetriNet
 * @brief Main container of Petri Net components
 */
class PetriNet 
{
public:
    QList<Place> places;
    QList<Transition> transitions;

    /**
     * @brief Adds a place to the petri net.
     * @param plc The place to add.
     */
    void addPlace(const Place &plc);

    /**
     * @brief Adds a transition to the petri net.
     * @param tr The transition to add.
     */
    void addTransition(const Transition &tr);

    /**
     * @brief Saves network state into JSON file
     * @param file_name Path to file.
     * @return if successful true, else false.
     */
    bool save(const QString &file_name) const;

    /**
     * @brief Loads network state from a file.
     * @param file_name Path to file.
     * @return if successful true, else false.
     */
    bool load(const QString& file_name);

};
