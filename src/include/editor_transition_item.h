/**
 * @file editor_transition_item.h
 *
 * @brief EditorTransitionItem definition 
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_node.h"

#include <QGraphicsRectItem>


class EditorArcItem;

/**
 * @brief QGraphicsItem for rendering transitions in the editor
 */
class EditorTransitionItem : public QGraphicsRectItem, public EditorNode  {
public:
    /**
     * @brief Editor transition
     */
    EditorTransitionItem();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    /**
     * @brief Removes and frees all the connected arcs 
     */
    void removeArcs() override;

    /**
     * @brief Draw the transition and it's id
     *
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    /**
     * @brief Increase bounding rect size to fit the transition and the id text
     */
    QRectF boundingRect() const override;

    /**
     * @brief Set the string id for the underlying Transition in the PetriNet model
     *
     * If the id currently set is also valid it changes the id in the Transition
     * in the PetriNet model as well.
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet
     *
     * @param id
     */
    void setId(std::string id);

    /**
     * @brief Get the string id for the underlying Transition in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     *
     * @returns id
     */
    std::string getId() const;

    /**
     * @brief Set the condition for the underlying Transition in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @param condition
     */
    void setGuardCondition(std::string condition);

    /**
     * @brief Get the current condition from the underlying Transition in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @returns condition
     */
    std::string getGuardCondition() const;

    /**
     * @brief Set the actions for the underlying Transition in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @param actions
     */
    void setActions(std::string actions);

    /**
     * @brief Get the current actions from the underlying Transition in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @returns actions
     */
    std::string getActions() const;

    /**
     * @brief Set the input event for the underlying Transition in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @param event
     */
    void setInputEvent(std::string event);
    
    /**
     * @brief Get the current input event from the underlying Transition in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @returns event
     */
    std::string getInputEvent() const;

    /**
     * @brief Set the delay for the underlying Transition in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @param delay
     */
    void setDelay(std::int64_t delay);

    /**
     * @brief Get the current delay from the underlying Transition in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @returns delay
     */
    std::int64_t getDelay() const;

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
