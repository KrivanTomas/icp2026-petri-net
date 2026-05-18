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

enum Event {create_place_, create_transition_, create_arc_, update_tokens_, fire_, log_message_};


/**
 * @class Observer
 * @brief Listens for events, is used by class Sender. 
 * 
 * To use, inherit this in your class and redefine the onEvent() functions you need.
 */
class Observer
{
    friend class Sender;

public:

    virtual ~Observer() {};
    /**
     * @brief Is called when any event is evoked for this observer's Subject. Fill this class with custom code.
     * @param event Evoked event type
     */
    virtual void onEvent(Event) {};
    /**
     * @brief Is called when any event is evoked for this observer's Subject. Fill this class with custom code.
     * 
     * This overload is used to receive an integer value.
     * @param event Evoked event type
     * @param a Value
     */
    virtual void onEvent(Event, int) {};
    /**
     * @brief Is called when any event is evoked for this observer's Subject. Fill this class with custom code.
     * 
     * This overload is used to receive a string value.
     * @param event Evoked event type
     * @param str Value
     */
    virtual void onEvent(Event, std::string) {};
    /**
     * @brief Is called when any event is evoked for this observer's Subject. Fill this class with custom code.
     * 
     * This overload is used to receive a string and an integer.
     * @param event Evoked event type
     * @param str String value
     * @param number Integer value
     */
    virtual void onEvent(Event, std::string, int) {};

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
    /**
     * @brief Notifies all current observers that something happened
     * 
     * This overload also sends an integer value
     * @param event Event type
     * @param number Value to send
     */
    void throwEvent(Event event, int number);
    /**
     * @brief Notifies all current observers that something happened
     * 
     * This overload also sends a string value
     * @param event Event type
     * @param str Value to send
     */
    void throwEvent(Event event, std::string str);
    /**
     * @brief Notifies all current observers that something happened
     * 
     * This overload also sends a string and an integer value
     * @param event Event type
     * @param str String value to send
     * @param number Integer value to send
     */
    void throwEvent(Event event, std::string str, int number);

private:
    Observer* observer_head;

};
