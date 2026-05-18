/**
 * @file editor_arc_item.h
 *
 * @brief EditorArcItem definition 
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_place_item.h"
#include "editor_transition_item.h"

#include <QGraphicsLineItem>

/**
 * @brief QGraphicsItem for rendering arcs in the editor
 */
class EditorArcItem : public QGraphicsLineItem {
public:
    /**
     * @brief Editor arc, this overload sets TO_TRANSITION as the arc's direction
     *
     * @param from
     * @param to
     * @param parent
     */
    EditorArcItem(EditorPlaceItem *from, EditorTransitionItem *to, QGraphicsItem *parent = nullptr);

    /**
     * @brief Editor arc, this overload sets TO_PLACE as the arc's direction
     *
     * @param from
     * @param to
     * @param parent
     */
    EditorArcItem(EditorTransitionItem *from, EditorPlaceItem *to, QGraphicsItem *parent = nullptr);

    /**
     * @brief Increase bounding rect size to fit the arc
     */
    QRectF boundingRect() const override;

    /**
     * @brief Add an arrow head to the arc
     */
    QPainterPath shape() const override;
    
    /**
     * @brief Draw the arc, calculates collision between the arc, place and trasition
     *
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    /**
     * @brief Forces the arc to recalculate it's position and redraw
     */
    void updatePosition();

    /**
     * @brief Set a temporary point to which to point when the `to` argument is not provided on construction 
     *
     * @param tmp
     */
    void setTempDestination(QPointF tmp);

    /**
     * @brief Set the place connected to this arc 
     *
     * @param place
     */
    void setPlace(EditorPlaceItem *place);

    /**
     * @brief Get the place connected to this arc 
     *
     * @return EditorPlaceItem pointer, can be nullptr
     */
    EditorPlaceItem *getPlace();

    /**
     * @brief Unset place pointer connected to this arc 
     */
    void unsetPlace();

    /**
     * @brief Set the transition connected to this arc 
     *
     * @param transition
     */
    void setTransition(EditorTransitionItem *transition);

    /**
     * @brief Get the transition connected to this arc 
     *
     * @return EditorTransitionItem pointer, can be nullptr
     */
    EditorTransitionItem *getTransition();

    /**
     * @brief Unset transition pointer connected to this arc 
     */
    void unsetTransition();

    /**
     * @brief Decides which way the arc points 
     */
    enum Direction { TO_PLACE, TO_TRANSITION };

    /**
     * @brief Get the arc direction decided upon arc construction
     *
     * @return arc direction
     */
    Direction getDirection();

    /**
     * @brief The arc is valid if both `from` and `to` is set
     *
     * @return true if valid else false
     */
    bool isValid();

    /**
     * @brief Set the string id for the underlying Arc in the PetriNet model
     *
     * If the id currently set is also valid it changes the id in the Arc
     * in the PetriNet model as well.
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     *
     * @param id
     */
    void setId(std::string id);

    /**
     * @brief Get the string id for the underlying Arc in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     *
     * @returns id
     */
    std::string getId() const;

    /**
     * @brief Set the weight for the underlying Arc in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @param weight
     */
    void setWeight(int weight);

    /**
     * @brief Get the current weight from the underlying Arc in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @returns weight
     */
    int getWeight() const;

    /**
     * @brief Set the source id for the underlying Arc in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @param source_id
     */
    void setSourceId(std::string source_id);

    /**
     * @brief Get the current source id from the underlying Arc in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @returns source id
     */
    std::string getSourceId() const;

    /**
     * @brief Set the target id for the underlying Arc in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @param target_id
     */
    void setTargetId(std::string target_id);

    /**
     * @brief Get the current target id from the underlying Arc in the PetriNet model
     *
     * @throws std::runtime_error if the object isn't connected to a PetriNet  
     * @throws std::runtime_error if the an object with the set id does not exist  
     *
     * @returns source id
     */
    std::string getTargetId() const;

protected:
    std::string model_id;
    Direction direction;
    EditorPlaceItem *place;
    QPointF tempDestination{};

    EditorTransitionItem *transition;
    QPolygonF arrowHead;
};
