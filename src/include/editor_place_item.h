/**
 * @file editor_place_item.h
 *
 * @brief Header for the editor place item class
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include <QGraphicsEllipseItem>

/**
 * @brief A graphic representation of a petri net place in the editor.
 */
class EditorPlaceItem : public QGraphicsEllipseItem {
public:
    /**
     * @brief Create a new place.
     */
    EditorPlaceItem();
};
