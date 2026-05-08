/**
 * @file editor_graphics_scene.h
 *
 * @brief Header for the main editor graphics scene
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_arc_item.h"

#include <QGraphicsScene>

/**
 * @brief `QGraphicsScene` for the editor.
 */
class EditorGraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    /**
     * @brief Create the editor scene.
     *
     * @param parent
     */
    EditorGraphicsScene(QObject *parent);

    /**
     * @brief Sets the mode of operation within the edior.
     */
    enum Mode { Insert, Edit };

    /**
     * @brief Sets the type of object to insert in insert mode.
     */
    enum InsertObject { Place, Transition, Arc };

public slots:
    /**
     * @brief Sets the editor mode.
     *
     * @param mode new value to be set
     */
    void setMode(Mode mode);
    /**
     * @brief Sets the editor mode to `Mode::Edit`.
     *
     * Calls `setMode()` internaly.
     */
    void setEditMode();
    /**
     * @brief Sets the editor mode to `Mode::Insert`.
     *
     * Calls `setMode()` internaly.
     */
    void setInsertMode();


    /**
     * @brief Sets the editor insert object.
     *
     * @param insert new value to be set
     */
    void setInsertObject(InsertObject insert);
    /**
     * @brief Sets the editor insert object to `InsertObject::Place`.
     *
     * Calls `setInsertObject()` internally.
     */
    void setInsertObjectPlace();
    /**
     * @brief Sets the editor insert object to `InsertObject::Transition`.
     *
     * Calls `setInsertObject()` internally.
     */
    void setInsertObjectTransition();
    /**
     * @brief Sets the editor insert object to `InsertObject::Arc`.
     *
     * Calls `setInsertObject()` internally.
     */
    void setInsertObjectArc();

signals:
    /**
     * @brief Emits every time a `setMode` or similar setter is called.
     *
     * @param mode new set value
     */
    void modeChanged(Mode mode);
    /**
     * @brief Emits every time a `setInsertObject` or similar setter is called.
     *
     * @param object new set value
     */
    void insertObjectChanged(InsertObject object);

protected:
    Mode editorMode;
    InsertObject insertObject;

    EditorArcItem *editedArc = nullptr;

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
};
