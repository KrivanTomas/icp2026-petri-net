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
}

void EditorGraphicsScene::setEditMode() {
    editorMode = Mode::Edit;
}

void EditorGraphicsScene::setInsertMode() {
    editorMode = Mode::Insert;
}

void EditorGraphicsScene::setInsertObject(InsertObject insert) {
    insertObject = insert;
}

void EditorGraphicsScene::setInsertObjectPlace() {
    insertObject = InsertObject::Place;
}

void EditorGraphicsScene::setInsertObjectTransition() {
    insertObject = InsertObject::Transition;
}

void EditorGraphicsScene::setInsertObjectArc() {
    insertObject = InsertObject::Arc;
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
            case InsertObject::Arc:
                break;
        }
    }
    
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void EditorGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void EditorGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
