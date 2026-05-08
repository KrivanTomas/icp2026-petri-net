/**
 * @file editor_graphics_scene.cpp
 *
 * @brief Contains a custom `QGraphicsScene` class for the petri net editor (`EditorGraphicsScene`)
 *
 * @author
 *     Tomáš Křivan
 */

#include "../include/editor_graphics_scene.h"
#include "../include/editor_place_item.h"
#include "../include/editor_transition_item.h"

#include <QGraphicsSceneMouseEvent>

EditorGraphicsScene::EditorGraphicsScene(QObject *parent) : QGraphicsScene(parent) {
    //setBackgroundBrush(QBrush(QColor(0,0,0), Qt::CrossPattern));
    editorMode = Mode::Edit;
    insertObject = InsertObject::Place;
}

void EditorGraphicsScene::setMode(Mode mode) {
    editorMode = mode;
    emit modeChanged(mode);
}

void EditorGraphicsScene::setEditMode() {
    setMode(Mode::Edit);
}

void EditorGraphicsScene::setInsertMode() {
    setMode(Mode::Insert);
}

void EditorGraphicsScene::setInsertObject(InsertObject insert) {
    insertObject = insert;
    emit insertObjectChanged(insert);
}

void EditorGraphicsScene::setInsertObjectPlace() {
    setInsertObject(InsertObject::Place);
}

void EditorGraphicsScene::setInsertObjectTransition() {
    setInsertObject(InsertObject::Transition);
}

void EditorGraphicsScene::setInsertObjectArc() {
    setInsertObject(InsertObject::Arc);
}


void EditorGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if(mouseEvent->button() != Qt::LeftButton) return;
        
    if(editorMode == Mode::Insert) {
        switch(insertObject) {
            case InsertObject::Place: {
                EditorPlaceItem *item;
                item = new EditorPlaceItem();
                item->setBrush(QBrush(QColor(255,255,255), Qt::SolidPattern));
                addItem(item);
                item->setPos(mouseEvent->scenePos());
                break;
                                      }
            case InsertObject::Transition: {
                EditorTransitionItem *item;
                item = new EditorTransitionItem();
                item->setBrush(QBrush(QColor(255,255,255), Qt::SolidPattern));
                addItem(item);
                item->setPos(mouseEvent->scenePos());
                break;
                                           }
            case InsertObject::Arc: {
                if(editedArc != nullptr) break;
                QList<QGraphicsItem*> start_items = items(mouseEvent->scenePos());

                while(start_items.count()) {
                    EditorPlaceItem *place = qgraphicsitem_cast<EditorPlaceItem*>(start_items.first());
                    if(place != nullptr) {
                        editedArc = new EditorArcItem(place, nullptr, nullptr);
                        addItem(editedArc);
                        break;
                    }
                    EditorTransitionItem *transition = qgraphicsitem_cast<EditorTransitionItem*>(start_items.first());
                    if(transition != nullptr) {
                        editedArc = new EditorArcItem(transition, nullptr, nullptr);
                        addItem(editedArc);
                        break;
                    }
                    start_items.removeFirst();
                }
                if(editedArc == nullptr) break;
                
                editedArc->setTempDestination(mouseEvent->scenePos());
                editedArc->updatePosition();

                break;
                                    }
        }
    }
    
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void EditorGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(editorMode == Mode::Edit) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        return;
    }
    if(editorMode == Mode::Insert && editedArc != nullptr) {
        QList<QGraphicsItem*> end_items = items(mouseEvent->scenePos());

        while(end_items.count()) {
            EditorPlaceItem *place = qgraphicsitem_cast<EditorPlaceItem*>(end_items.first());
            if(place != nullptr && editedArc->getDirection() == EditorArcItem::Direction::TO_PLACE) {
                editedArc->setPlace(place);
                editedArc->updatePosition();
                return;
            }
            EditorTransitionItem *transition = qgraphicsitem_cast<EditorTransitionItem*>(end_items.first());
            if(transition != nullptr && editedArc->getDirection() == EditorArcItem::Direction::TO_TRANSITION) {
                editedArc->setTransition(transition);
                editedArc->updatePosition();
                return;
            }
            end_items.removeFirst();
        }

        if(editedArc->getDirection() == EditorArcItem::Direction::TO_PLACE) {
            editedArc->unsetPlace();
        }
        else if(editedArc->getDirection() == EditorArcItem::Direction::TO_TRANSITION) {
            editedArc->unsetTransition();
        }
        
        editedArc->setTempDestination(mouseEvent->scenePos());
        editedArc->updatePosition();
        return;
    }
}

void EditorGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    if(editedArc != nullptr) {
        // TODO place arc if valid
        if(!editedArc->isValid()) {
            removeItem(editedArc);
            delete editedArc;
        }
        else {
            editedArc->getPlace()->addArc(editedArc);
            editedArc->getTransition()->addArc(editedArc);
        }
        editedArc = nullptr;
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
