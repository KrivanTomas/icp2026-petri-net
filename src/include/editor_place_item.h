/**
 * @file editor_place_item.h
 *
 * @brief Header for the editor place item class
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_node.h"

#include <QGraphicsEllipseItem>

class EditorArcItem;

/**
 * @brief A graphic representation of a petri net place in the editor.
 */
class EditorPlaceItem : public QGraphicsEllipseItem, public EditorNode {
public:
    /**
     * @brief Create a new place.
     */
    EditorPlaceItem();

    qreal radius = 0;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }
    void removeArcs() override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};
