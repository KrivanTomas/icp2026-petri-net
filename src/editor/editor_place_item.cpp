/**
 * @file editor_place_item.cpp
 *
 * @brief Contains the `EditorPlaceItem` class for rendering petri net place objects.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_place_item.h"

EditorPlaceItem::EditorPlaceItem() : QGraphicsEllipseItem(-50,-50,100,100) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}
