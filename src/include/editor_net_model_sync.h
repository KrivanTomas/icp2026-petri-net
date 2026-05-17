/**
 * @file editor_net_model_sync.h
 *
 * @brief Header containing a utility for syncing state between the internal petri net model and the gui scene.
 *
  * @author
 *     Tomáš Křivan
 */

#pragma once

#include "petrinet.h"
#include "editor_graphics_scene.h"

class EditorNetModelSceneSync {
public:
    static void syncSceneWithModel(EditorGraphicsScene *scene);
    static std::string generatePlaceName();
    static std::string generateTransitionName();
    static std::string generateArcName();
    static PetriNet *getCurrentNet();
    static void setCurrentNet(PetriNet *net);
private:
    static PetriNet *net;
    static unsigned int place_counter;
    static unsigned int transition_counter;
    static unsigned int arc_counter;
};
