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
#include "../include/editor_net_model_sync.h"

#include <QPen>
#include <QGraphicsScene>
#include <iostream>

EditorPlaceItem::EditorPlaceItem() : QGraphicsEllipseItem(-50,-50,100,100) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    radius = 100 / 2.0;

    setBrush(QBrush(QColor(255,255,255), Qt::SolidPattern));
    setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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

void EditorPlaceItem::setId(std::string id) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getPlaces().find(model_id) != net->getPlaces().end()) {
        // change model if exists
        net->changePlaceId(model_id, id);
    }
    model_id = id;
}

std::string EditorPlaceItem::getId() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    return model_id;
}

void EditorPlaceItem::setTokens(int tokens) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getPlaces().find(model_id) == net->getPlaces().end()) throw std::runtime_error("setTokens(): Model desync");
    net->getPlaces().at(model_id).setCurrentTokens(tokens);
}

int EditorPlaceItem::getTokens() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getPlaces().find(model_id) == net->getPlaces().end()) throw std::runtime_error("getTokens(): Model desync");

    return net->getPlaces().at(model_id).getCurrentTokens();
}

void EditorPlaceItem::setActions(std::string actions) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getPlaces().find(model_id) == net->getPlaces().end()) throw std::runtime_error("setActions(): Model desync");

    net->getPlaces().at(model_id).setActionCode(actions);
}

std::string EditorPlaceItem::getActions() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getPlaces().find(model_id) == net->getPlaces().end()) throw std::runtime_error("getActions(): Model desync");

    return net->getPlaces().at(model_id).getActionCode();
}
