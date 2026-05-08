/**
 * @file editor_node_item.h
 *
 * @brief Header for the editor node item class
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include <QGraphicsItem>

class EditorArcItem;

class EditorNode {
public:
    void addArc(EditorArcItem *arc);
    void removeArc(EditorArcItem *arc);
    virtual void removeArcs() = 0;

protected:
    QList<EditorArcItem*> arcs;
};
