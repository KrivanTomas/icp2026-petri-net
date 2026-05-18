/**
 * @file editor_node.h
 *
 * @brief EditorNode definition 
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include <QGraphicsItem>

class EditorArcItem;

/**
 * @brief Abstract class for representing graphics items able to be connected with arcs
 */
class EditorNode {
public:
    /**
     * @brief Connect an arc
     * 
     * @param arc
     */
    void addArc(EditorArcItem *arc);

    /**
     * @brief Disconnect an arc
     * 
     * @param arc
     */
    void removeArc(EditorArcItem *arc);

    /**
     * @brief Get a list of the currently connected arcs
     * 
     * @return arc list
     */
    QList<EditorArcItem*>& getArcs();

    /**
     * @brief Remove and free all of the connected arcs 
     */
    virtual void removeArcs() = 0;

protected:
    /**
     * @brief List of the currently connected arcs
     */
    QList<EditorArcItem*> arcs;
};
