/**
 * @file editor_place_item.cpp
 *
 * @brief Contains the `EditorPlaceItem` class for rendering petri net place objects.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_place_item.h"
#include "../include/editor_arc_item.h"

#include <QPen>
#include <QGraphicsScene>

EditorPlaceItem::EditorPlaceItem() : QGraphicsEllipseItem(-50,-50,100,100) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    radius = 100 / 2.0;

    QPen pen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(pen);
}

QVariant EditorPlaceItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (EditorArcItem *arc : arcs)
            arc->updatePosition();
    }

    return value;
}

void EditorPlaceItem::removeArcs()
{
    const auto arcs_copy = arcs;
    for (EditorArcItem *arc : arcs_copy) {
        if(arc->getPlace() != nullptr)
            arc->getPlace()->removeArc(arc);
        if(arc->getTransition() != nullptr)
            arc->getTransition()->removeArc(arc);
        scene()->removeItem(arc);
        delete arc;
    }
}
