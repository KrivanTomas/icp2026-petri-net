/**
 * @file editor_net_model_sync.cpp
 *
 * @brief Utilities to help with syncing the internal petri net model with the gui scene.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_net_model_sync.h"


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
    }
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
