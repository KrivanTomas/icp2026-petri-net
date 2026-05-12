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
#include <vector>

enum Event {create_place_, create_transition_, create_arc_, update_tokens_, fire_};


/**
 * @class Observer
 * @brief Listens for events, is used by class Subject. To use, inherit this in your class and redefine the onEvent() function.
 */
class Observer
{
    friend class Sender;

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
    virtual void onEvent(Event event, int a) {event = event;a=a;}

private:
    Observer* obs_next;
    Observer* obs_previous;
};

/**
 * @brief Sender class to "store" observers and notify them of events this class makes by throwEvent().
 */
class Sender
{
public:

    /**
     * @brief Constructor of a subject
     */
    Sender();

    /**
     * @brief Adds an observer to this subject's list of listeners
     * @param observer Pointer to the observer
     */
    void addObserver(Observer* sender);

    /**
     * @brief Removes an observer from this subject's list of listeners
     * @param observer Pointer to the observer
     */
    void removeObserver(Observer* sender);

    /**
     * @brief Notifies all current observers that something happened
     * @param event Event type
     */
    void throwEvent(Event event);
    void throwEvent(Event event, int a);

private:
    Observer* observer_head;

};
