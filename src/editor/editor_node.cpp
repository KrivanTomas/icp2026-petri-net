/**
 * @file editor_node_item.cpp
 *
 * @brief Contains the `EditorNodeItem` class for rendering petri net node-like objects.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_node.h"

void EditorNode::addArc(EditorArcItem *arc) {
    arcs.append(arc);
}

void EditorNode::removeArc(EditorArcItem *arc) {
    arcs.removeAll(arc);
}
