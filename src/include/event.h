/**
 * @file event.h
 *
 * @brief Simulation of the petrinet
 *
 * @author
 *     Lukáš Kurtin
 */
#pragma once

#include <iostream>

enum Event {create_place_, create_transition_, create_arc_, update_tokens_, fire_};


/**
 * @class Observer
 * @brief Listens for events, is used by class Subject. To use, inherit this in your class and redefine the onEvent() function.
 */
class Observer
{
    friend class Subject;

public:
    /**
     * @brief Constructor of an observer
     */
    Observer();

    /**
     * @brief Destructor of an observer
     */
    virtual ~Observer() {}

    /**
     * @brief Is called when any event is evoked for this observer's Subject. Fill this class with custom code.
     * @param event Evoked event type
     */
    virtual void onEvent(Event event) {event = event;}


private:
    Observer* list_next;
    Observer* list_previous;
};

/**
 * @brief Subject class to "store" observers and notify them of events this class makes by throwEvent().
 */
class Subject 
{
public:

    /**
     * @brief Constructor of a subject
     */
    Subject();

    /**
     * @brief Adds an observer to this subject's list of listeners
     * @param observer Pointer to the observer
     */
    void addObserver(Observer* observer);

    /**
     * @brief Removes an observer from this subject's list of listeners
     * @param observer Pointer to the observer
     */
    void removeObserver(Observer* observer);

protected:
    /**
     * @brief Notifies all current observers that something happened
     * @param event Event type
     */
    void throwEvent(Event event);

private:
    Observer* list_head;
};
