/**
 * @file editor_arc_item.h
 *
 * @brief Header for the editor arc item class
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_place_item.h"
#include "editor_transition_item.h"

#include <QGraphicsLineItem>

class EditorArcItem : public QGraphicsLineItem {
public:
    EditorArcItem(EditorPlaceItem *from, EditorTransitionItem *to, QGraphicsItem *parent);
    EditorArcItem(EditorTransitionItem *from, EditorPlaceItem *to, QGraphicsItem *parent);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void updatePosition();
    void setTempDestination(QPointF tmp);

    void setPlace(EditorPlaceItem *place);
    EditorPlaceItem *getPlace();
    void unsetPlace();
    void setTransition(EditorTransitionItem *transition);
    EditorTransitionItem *getTransition();
    void unsetTransition();

    enum Direction { TO_PLACE, TO_TRANSITION };
    Direction getDirection();

    bool isValid();

protected:
    Direction direction;
    EditorPlaceItem *place;
    QPointF tempDestination{};

    EditorTransitionItem *transition;
    QPolygonF arrowHead;
};
