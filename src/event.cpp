
/**
 * @file event.cpp
 *
 * @brief Simulation of the petrinet
 *
 * @author
 *     Lukáš Kurtin
 */

#include "../include/event.h"

Observer::Observer():obs_next(NULL), obs_previous(NULL){};


Sender::Sender():observer_head(NULL) {};

void Sender::throwEvent(Event event) {
    Observer* obs = observer_head;
    while(obs != NULL) {
        obs->onEvent(event);
        obs = obs->obs_next;
    }
}
void Sender::throwEvent(Event event, int a) {
    Observer* obs = observer_head;
    while(obs != NULL) {
        obs->onEvent(event, a);
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