/**
 * @file editor_transition_item.cpp
 *
 * @brief Contains the `EditorTransitionItem` class for rendering petri net transition objects.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_transition_item.h"
#include "../include/editor_arc_item.h"

#include <QPen>
#include <QGraphicsScene>

EditorTransitionItem::EditorTransitionItem() : QGraphicsRectItem(-25,-50,50,100) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    QPen pen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    setPen(pen);
}

QVariant EditorTransitionItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (EditorArcItem *arc : arcs) {
            arc->updatePosition();
        }
    }

    return value;
}

void EditorTransitionItem::removeArcs()
{
    const auto arcs_copy = arcs;
    for (EditorArcItem *arc : arcs_copy) {
        if(arc->getPlace())
            arc->getPlace()->removeArc(arc);
        if(arc->getTransition())
            arc->getTransition()->removeArc(arc);
        scene()->removeItem(arc);
        delete arc;
    }
}
