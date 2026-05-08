/**
 * @file editor_arc_item.cpp
 *
 * @brief Contains the `EditorArcItem` class for rendering petri net arcs between `EditorPlaceItem` and `EditorTransitionItem`.
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_arc_item.h"

#include <QPen>
#include <QPainter>
#include <cmath>

EditorArcItem::EditorArcItem(EditorPlaceItem *from, EditorTransitionItem *to, QGraphicsItem *parent) :
        QGraphicsLineItem(parent), place(from), transition(to) {
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setZValue(-1000);

    direction = Direction::TO_TRANSITION;
}

EditorArcItem::EditorArcItem(EditorTransitionItem *from, EditorPlaceItem *to, QGraphicsItem *parent) :
        QGraphicsLineItem(parent), place(to), transition(from) {
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setZValue(-1000);

    direction = Direction::TO_PLACE;
}

QRectF EditorArcItem::boundingRect() const {
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath EditorArcItem::shape() const {
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void EditorArcItem::updatePosition()
{
    QLineF line;
    if(place && transition) {
        if(direction == Direction::TO_PLACE) {
            line = QLineF(mapFromItem(place, 0, 0), mapFromItem(transition, 0, 0));
        }
        else if(direction == Direction::TO_TRANSITION) {
            line = QLineF(mapFromItem(transition, 0, 0), mapFromItem(place, 0, 0));
        }
    }
    else if(place || transition) {
        if(direction == Direction::TO_PLACE) {
            line = QLineF(mapFromItem(place, 0, 0), tempDestination);
        }
        else if(direction == Direction::TO_TRANSITION) {
            line = QLineF(mapFromItem(transition, 0, 0), tempDestination);
        }
    }
    setLine(line);
}

void EditorArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (place && transition && place->collidesWithItem(transition))
        return;


    QColor myColor = Qt::black;
    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);


    if(direction == Direction::TO_TRANSITION) {
        if(transition == nullptr) {
            setLine(QLineF(tempDestination, place->pos()));
        }
        else {
            QLineF centerLine(place->pos(), transition->pos());
            QPolygonF endPolygon = transition->rect();
            QPointF p1 = endPolygon.first() + transition->pos();
            QPointF intersectPoint;
            for (int i = 1; i < endPolygon.count(); ++i) {
                QPointF p2 = endPolygon.at(i) + transition->pos();
                QLineF polyLine = QLineF(p1, p2);
                QLineF::IntersectionType intersectionType =
                    polyLine.intersects(centerLine, &intersectPoint);
                if (intersectionType == QLineF::BoundedIntersection)
                    break;
                p1 = p2;
            }
            setLine(QLineF(intersectPoint, place->pos()));
        }
    }
    else if(direction == Direction::TO_PLACE) {
        if(place == nullptr) {
            setLine(QLineF(tempDestination, transition->pos()));
        }
        else {
            // this is is backwards for setLenght()
            QLineF centerLine(transition->pos(), place->pos());

            centerLine.setLength(centerLine.length() - place->radius);
            
            setLine(QLineF(centerLine.p2(), centerLine.p1()));
        }
    }


    double angle = std::atan2(-line().dy(), line().dx());

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                    cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                    cos(angle + M_PI - M_PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;

    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}

bool EditorArcItem::isValid() {
    return place && transition;
}

EditorArcItem::Direction EditorArcItem::getDirection() {
    return direction;
}

void EditorArcItem::setTempDestination(QPointF tmp) {
    tempDestination = tmp;
}

void EditorArcItem::setPlace(EditorPlaceItem *place) {
    this->place = place;
}

EditorPlaceItem *EditorArcItem::getPlace() {
    return place;
}

void EditorArcItem::unsetPlace() {
    this->place = nullptr;
}

void EditorArcItem::setTransition(EditorTransitionItem *transition) {
    this->transition = transition;
}

EditorTransitionItem *EditorArcItem::getTransition() {
    return transition;
}

void EditorArcItem::unsetTransition() {
    this->transition = nullptr;
}

