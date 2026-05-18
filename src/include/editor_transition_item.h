/**
 * @file editor_transition_item.h
 *
 * @brief Header for the editor transition item class
 *
 * @author
 *     Tomáš Křivan
 */

#pragma once

#include "editor_node.h"

#include <QGraphicsRectItem>


class EditorArcItem;

/**
 * @brief A graphic representation of a petri net transiton in the editor.
 */
class EditorTransitionItem : public QGraphicsRectItem, public EditorNode  {
public:
    /**
     * @brief Create a new transiton.
     */
    EditorTransitionItem();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }
    void removeArcs() override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

    void setId(std::string id);
    std::string getId() const;

    void setGuardCondition(std::string condition);
    std::string getGuardCondition() const;

    void setActions(std::string actions);
    std::string getActions() const;

    void setInputEvent(std::string event);
    std::string getInputEvent() const;

    void setDelay(std::int64_t delay);
    std::int64_t getDelay() const;

protected:
    std::string model_id;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};
