
/**
 * @file event.cpp
 *
 * @brief Simulation of the petrinet
 *
 * @author
 *     Lukáš Kurtin
 */

#include "include/event.h"


Sender::Sender():observer_head(NULL) {};

void Sender::throwEvent(Event event) {
    Observer* obs = observer_head;
    while(obs != NULL) {
        obs->onEvent(event);
        obs = obs->obs_next;
    }
}
void Sender::throwEvent(Event event, int number) {
    Observer* obs = observer_head;
    while(obs != NULL) {
        obs->onEvent(event, number);
        obs = obs->obs_next;
    }
}
void Sender::throwEvent(Event event, std::string str) {
    Observer* obs = observer_head;
    while(obs != NULL) {
        obs->onEvent(event, str);
        obs = obs->obs_next;
    }
}

void Sender::throwEvent(Event event, std::string str, int number) {
    Observer* obs = observer_head;
    while(obs != nullptr) {
        obs->onEvent(event, str, number);
        obs = obs->obs_next;
    }
}


void Sender::addObserver(Observer* observer) {
    observer->obs_next = observer_head;
    observer_head = observer;
}

void Sender::removeObserver(Observer* observer){

    //observer is first in list
    if(observer == observer_head) {
        observer_head = observer->obs_next;
        observer->obs_next = NULL;
        return;
    }

    //observer is anywhere except head
    observer->obs_previous->obs_next = observer->obs_next;
    observer->obs_next = NULL;
}