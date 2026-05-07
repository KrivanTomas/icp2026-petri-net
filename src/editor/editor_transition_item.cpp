/**
 * @file editor_transition_item.cpp
 *
 * @brief Contains the `EditorTransitionItem` class for rendering petri net transition objects.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_transition_item.h"

EditorTransitionItem::EditorTransitionItem() : QGraphicsRectItem(-25,-50,50,100) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}
