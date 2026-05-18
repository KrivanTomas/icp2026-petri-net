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
#include "../include/editor_net_model_sync.h"

#include <QPen>
#include <QPainter>
#include <QGraphicsScene>

EditorTransitionItem::EditorTransitionItem() : QGraphicsRectItem(-25,-50,50,100) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setBrush(QBrush(QColor(255,255,255), Qt::SolidPattern));
    setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}


void EditorTransitionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    this->QGraphicsRectItem::paint(painter, option, widget);


    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) return; 
    if(net->getTransitions().find(model_id) != net->getTransitions().end()) {
        std::string id = net->getTransitions().at(model_id).getId();

        // draw id
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        QFont font = painter->font();
        font.setPixelSize(24);
        font.setBold(true);
        painter->setFont(font);
        painter->drawText(QRect(-100, -80, 200, 30), Qt::AlignCenter, QString::fromStdString(id));
    }
}

QRectF EditorTransitionItem::boundingRect() const {
    return QRectF(-100, -80, 200, 130);
}



QVariant EditorTransitionItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        for (EditorArcItem *arc : arcs) {
            arc->updatePosition();
        }
        setPosition(pos());
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

void EditorTransitionItem::setId(std::string id) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) != net->getTransitions().end()) {
        // change in model if exists
        net->changeTransitionId(model_id, id);
    }
    model_id = id;
}

std::string EditorTransitionItem::getId() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    return model_id;
}

void EditorTransitionItem::setDelay(std::int64_t delay) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end()) 
        throw std::runtime_error("EditorTransitionItem::setDelay(): Model desync");
    net->getTransitions().at(model_id).setDelay(delay);
}

std::int64_t EditorTransitionItem::getDelay() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end())
        throw std::runtime_error("EditorTransitionItem::getDelay(): Model desync");

    return net->getTransitions().at(model_id).getDelay();
}

void EditorTransitionItem::setActions(std::string actions) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end())
        throw std::runtime_error("EditorTransitionItem::setActions(): Model desync");

    net->getTransitions().at(model_id).setActionCode(actions);
}

std::string EditorTransitionItem::getActions() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end())
        throw std::runtime_error("EditorTransitionItem::getActions(): Model desync");

    return net->getTransitions().at(model_id).getActionCode();
}

void EditorTransitionItem::setGuardCondition(std::string condition) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end())
        throw std::runtime_error("EditorTransitionItem::setGuardCondition(): Model desync");

    net->getTransitions().at(model_id).setGuardCondition(condition);
}

std::string EditorTransitionItem::getGuardCondition() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end())
        throw std::runtime_error("EditorTransitionItem::getGuardCondition(): Model desync");

    return net->getTransitions().at(model_id).getGuardCondition();
}

void EditorTransitionItem::setInputEvent(std::string event) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end())
        throw std::runtime_error("EditorTransitionItem::setInputEvent(): Model desync");

    net->getTransitions().at(model_id).setInputEventName(event);
}

std::string EditorTransitionItem::getInputEvent() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end())
        throw std::runtime_error("EditorTransitionItem::getInputEvent(): Model desync");

    return net->getTransitions().at(model_id).getInputEventName();
}

void EditorTransitionItem::setPosition(QPointF pos) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end())
        throw std::runtime_error("EditorPlaceItem::setPosition(): Model desync");

    net->getTransitions().at(model_id).setPosition(pos.x(), pos.y());
}

QPointF EditorTransitionItem::getPosition() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getTransitions().find(model_id) == net->getTransitions().end())
        throw std::runtime_error("EditorPlaceItem::getPosition(): Model desync");

    auto pair = net->getTransitions().at(model_id).getPosition();
    return QPointF(pair.first, pair.second);
}
