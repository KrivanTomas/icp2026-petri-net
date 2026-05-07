
/**
 * @file event.cpp
 *
 * @brief Simulation of the petrinet
 *
 * @author
 *     Lukáš Kurtin
 */

#include "../include/event.h"

Observer::Observer():list_next(NULL), list_previous(NULL) {};


Subject::Subject():list_head(NULL) {};

void Subject::throwEvent(Event event) {
    Observer* obs = list_head;
    while(obs != NULL) {
        obs->onEvent(event);
        obs = obs->list_next;
    }
}

void Subject::addObserver(Observer* observer) {
    observer->list_next = list_head;
    list_head = observer;
}

void Subject::removeObserver(Observer* observer){

    //observer is first in list
    if(observer == list_head) {
        list_head = observer->list_next;
        observer->list_next = NULL;
        return;
    }

    //observer is anywhere except head
    observer->list_previous->list_next = observer->list_next;
    observer->list_next = NULL;
}