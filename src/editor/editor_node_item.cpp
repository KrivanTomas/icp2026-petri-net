/**
 * @file editor_node_item.cpp
 *
 * @brief Contains the `EditorNodeItem` class for rendering petri net node-like objects.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_node_item.h"

EditorNodeItem::EditorNodeItem() : QGraphicsItem() {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}
