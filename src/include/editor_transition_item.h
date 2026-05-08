/**
 * @file editor_transition_item.h
 *
 * @brief Header for the editor transition item class
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_node.h"

#include <QGraphicsRectItem>


class EditorArcItem;

/**
 * @brief A graphic representation of a petri net transiton in the editor.
 */
class EditorTransitionItem : public QGraphicsRectItem, public EditorNode  {
public:
    /**
     * @brief Create a new transiton.
     */
    EditorTransitionItem();


    enum { Type = UserType + 2 };
    int type() const override { return Type; }
    void removeArcs() override;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};
