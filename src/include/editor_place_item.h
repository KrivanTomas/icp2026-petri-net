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

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    
    void setId(std::string id);
    std::string getId() const;

    void setTokens(int tokens);
    int getTokens() const;

    void setActions(std::string actions);
    std::string getActions() const;

protected:
    std::string model_id;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};
