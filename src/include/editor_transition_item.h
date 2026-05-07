/**
 * @file editor_transition_item.h
 *
 * @brief Header for the editor transition item class
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include <QGraphicsRectItem>

/**
 * @brief A graphic representation of a petri net transiton in the editor.
 */
class EditorTransitionItem : public QGraphicsRectItem {
public:
    /**
     * @brief Create a new transiton.
     */
    EditorTransitionItem();
};
