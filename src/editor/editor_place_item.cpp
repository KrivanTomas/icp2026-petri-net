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
#include <QPainter>

EditorPlaceItem::EditorPlaceItem() : QGraphicsEllipseItem(-50,-50,100,100) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    radius = 100 / 2.0;
    setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setBrush(QBrush(QColor(255,255,255), Qt::SolidPattern));
}
    
void EditorPlaceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    this->QGraphicsEllipseItem::paint(painter, option, widget);


    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) return; 
    if(net->getPlaces().find(model_id) != net->getPlaces().end()) {
        int tokens = net->getPlaces().at(model_id).getCurrentTokens();
        std::string id = net->getPlaces().at(model_id).getId();

        // draw id
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        QFont font = painter->font();
        font.setPixelSize(24);
        font.setBold(true);
        painter->setFont(font);
        painter->drawText(QRect(-100, -80, 200, 30), Qt::AlignCenter, QString::fromStdString(id));

        // prepare painter for tokens
        painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));


        // draw tokens
        int token_size = 18;
        int spacing = 22;
        if(tokens <= 0) return;
        else if(tokens == 1) {
            painter->drawEllipse(-token_size / 2.0, -token_size / 2.0, token_size, token_size);
        }
        else if(tokens == 2) {
            painter->drawEllipse(-token_size / 2.0 - spacing, -token_size / 2.0, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 + spacing, -token_size / 2.0, token_size, token_size);
        }
        else if(tokens == 3) {
            painter->drawEllipse(-token_size / 2.0, -token_size / 2.0 - spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 - spacing, -token_size / 2.0 + spacing * 0.66, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 + spacing, -token_size / 2.0 + spacing * 0.66, token_size, token_size);
        }
        else if(tokens == 4) {
            painter->drawEllipse(-token_size / 2.0 - spacing, -token_size / 2.0 - spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 - spacing, -token_size / 2.0 + spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 + spacing, -token_size / 2.0 - spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 + spacing, -token_size / 2.0 + spacing, token_size, token_size);
        }
        else if(tokens == 5) {
            painter->drawEllipse(-token_size / 2.0 - spacing, -token_size / 2.0 - spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 - spacing, -token_size / 2.0 + spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 + spacing, -token_size / 2.0 - spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 + spacing, -token_size / 2.0 + spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0, -token_size / 2.0, token_size, token_size);
        }
        else if(tokens == 6) {
            painter->drawEllipse(-token_size / 2.0 - spacing, -token_size / 2.0, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 + spacing, -token_size / 2.0, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 - spacing, -token_size / 2.0 - spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 - spacing, -token_size / 2.0 + spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 + spacing, -token_size / 2.0 - spacing, token_size, token_size);
            painter->drawEllipse(-token_size / 2.0 + spacing, -token_size / 2.0 + spacing, token_size, token_size);
        }
        else {
            painter->drawText(rect(), Qt::AlignCenter, QString::fromStdString(std::to_string(tokens)));
        }
    }
}


QRectF EditorPlaceItem::boundingRect() const {
    return QRectF(-100, -80, 200, 130);
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
    update();
}

std::string EditorPlaceItem::getId() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    return model_id;
}

void EditorPlaceItem::setTokens(int tokens) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getPlaces().find(model_id) == net->getPlaces().end())
        throw std::runtime_error("EditorPlaceItem::setTokens(): Model desync");
    net->getPlaces().at(model_id).setCurrentTokens(tokens);
    update();
}

int EditorPlaceItem::getTokens() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getPlaces().find(model_id) == net->getPlaces().end())
        throw std::runtime_error("EditorPlaceItem::getTokens(): Model desync");

    return net->getPlaces().at(model_id).getCurrentTokens();
}

void EditorPlaceItem::setActions(std::string actions) {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getPlaces().find(model_id) == net->getPlaces().end())
        throw std::runtime_error("EditorPlaceItem::setActions(): Model desync");

    net->getPlaces().at(model_id).setActionCode(actions);
}

std::string EditorPlaceItem::getActions() const {
    PetriNet *net = EditorNetModelSceneSync::getCurrentNet();
    if(net == nullptr) throw std::runtime_error("PetriNet sync not set");
    if(net->getPlaces().find(model_id) == net->getPlaces().end())
        throw std::runtime_error("EditorPlaceItem::getActions(): Model desync");

    return net->getPlaces().at(model_id).getActionCode();
}
