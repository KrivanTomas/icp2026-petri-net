/**
 * @file editor_graphics_scene.h
 *
 * @brief Header for the main editor graphics scene
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include <QGraphicsScene>

class EditorGraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    EditorGraphicsScene(QObject *parent);
    enum Mode { Insert, Edit };
    enum InsertObject { Place, Transition, Arc };

public slots:
    void setMode(Mode mode);
    void setEditMode();
    void setInsertMode();

    void setInsertObject(InsertObject insert);
    void setInsertObjectPlace();
    void setInsertObjectTransition();
    void setInsertObjectArc();

protected:
    Mode editorMode;
    InsertObject insertObject;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
};
