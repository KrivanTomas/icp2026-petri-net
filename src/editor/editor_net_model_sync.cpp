/**
 * @file editor_net_model_sync.cpp
 *
 * @brief Utilities to help with syncing the internal petri net model with the gui scene.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_net_model_sync.h"
#include "../include/editor_arc_item.h"

#include <iostream>

unsigned int EditorNetModelSceneSync::place_counter = 1;
unsigned int EditorNetModelSceneSync::transition_counter = 1;
unsigned int EditorNetModelSceneSync::arc_counter = 1;

PetriNet *EditorNetModelSceneSync::net = nullptr;

void EditorNetModelSceneSync::syncSceneWithModel(EditorGraphicsScene *scene) {
    // Clean up scene
    scene->clear();

    // Insert places from model
    for(const auto& pair : net->getPlaces()) {
        EditorPlaceItem *item = new EditorPlaceItem();

        item->setId(pair.first);
        scene->addItem(item);
        item->setPos(item->getPosition());
    }

    // Insert transitions from model
    for(const auto& pair : net->getTransitions()) {
        EditorTransitionItem *item = new EditorTransitionItem();

        item->setId(pair.first);
        scene->addItem(item);
        item->setPos(item->getPosition());
    }

    // Insert arcs from model
    for(const auto& pair : net->getArcs()) {
        std::string from_id = pair.second.getSourceId();
        std::string to_id = pair.second.getTargetId();


        EditorPlaceItem *from_place = nullptr;
        EditorTransitionItem *from_transition = nullptr;
        EditorPlaceItem *to_place = nullptr;
        EditorTransitionItem *to_transition = nullptr;
        // get the required pointers by going through all of the
        // graphics items and compare method_id, slow but works
        for(QGraphicsItem *item : scene->items()) {
            from_place = qgraphicsitem_cast<EditorPlaceItem*>(item);   
            if(from_place && from_place->getId() == from_id) {
                break;
            }
            from_place = nullptr;
            from_transition = qgraphicsitem_cast<EditorTransitionItem*>(item);   
            if(from_transition && from_transition->getId() == from_id) {
                break;
            }
            from_transition = nullptr;
        }
        for(QGraphicsItem *item : scene->items()) {
            to_place = qgraphicsitem_cast<EditorPlaceItem*>(item);   
            if(to_place && to_place->getId() == to_id) {
                break;
            }
            to_place = nullptr;
            to_transition = qgraphicsitem_cast<EditorTransitionItem*>(item);   
            if(to_transition && to_transition->getId() == to_id) {
                break;
            }
            to_transition = nullptr;
        }

        EditorArcItem *item = nullptr;
        if(from_place && to_transition) {
            item = new EditorArcItem(from_place, to_transition);
        }
        else if(from_transition && to_place) {
            item = new EditorArcItem(from_transition, to_place);
        }
        else {
            throw std::runtime_error("Could not sync model: invalid arc");
        }

        item->setId(pair.first);
        scene->addItem(item);
        item->updatePosition();
    }
}

void EditorNetModelSceneSync::resetCounters() {
    place_counter = 1;
    transition_counter = 1;
    arc_counter = 1;
}

std::string EditorNetModelSceneSync::generatePlaceName() {
    return "P" + std::to_string(place_counter++);
}

std::string EditorNetModelSceneSync::generateTransitionName() {
    return "T" + std::to_string(transition_counter++);
}

std::string EditorNetModelSceneSync::generateArcName() { 
    return "A" + std::to_string(arc_counter++);
}

PetriNet *EditorNetModelSceneSync::getCurrentNet() {
    return net;
}

void EditorNetModelSceneSync::setCurrentNet(PetriNet *net) {
    EditorNetModelSceneSync::net = net;
}
