/**
 * @file editor_place_item.h
 *
 * @brief EditorPlaceItem definition 
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_node.h"

#include <QGraphicsEllipseItem>

class EditorArcItem;

/**
 * @brief QGraphicsItem for rendering places in the editor
 */
class EditorPlaceItem : public QGraphicsEllipseItem, public EditorNode {
public:
    /**
     * @brief Editor place
     */
    EditorPlaceItem();

    qreal radius = 0;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    /**
     * @brief Removes and frees all the connected arcs 
     */
    void removeArcs() override;

    /**
     * @brief Draw the place with tokens and place id
     *
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    /**
     * @brief Increase bounding rect size to fit the place and the id text
     */
    QRectF boundingRect() const override;
    
    /**
     * @brief Set the string id for the underlying Place in the PetriNet model
     *
     * If the id currently set is also valid it changes the id in the Places
     * in the PetriNet model as well.
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     *
     * @param id
     */
    void setId(std::string id);

    /**
     * @brief Get the string id for the underlying Place in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     *
     * @returns id
     */
    std::string getId() const;

    /**
     * @brief Set the tokens for the underlying Place in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @param place
     */
    void setTokens(int tokens);

    /**
     * @brief Get the current tokens from the underlying Place in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @returns tokens
     */
    int getTokens() const;

    /**
     * @brief Set the actions for the underlying Place in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @param actions
     */
    void setActions(std::string actions);

    /**
     * @brief Get the current actions from the underlying Place in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @returns actions
     */
    std::string getActions() const;

protected:
    std::string model_id;

    /**
     * @brief Updates the connected arcs when moving this item 
     *
     * @param change
     * @param value
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};
