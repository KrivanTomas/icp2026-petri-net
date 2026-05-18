/**
 * @file arc.h
 *
 * @brief Header file for arcs
 *
 * @author
 *     Tomáš Kudera
 */
#pragma once

#include <string>

/**
 * @class Arc
 * @brief Třída pro reprezentaci orientovaných hran v petriho síti
 * 
 * propojení míst a přechodů 
 */
class Arc
{
public:
    /**
     * @brief Constructor of an Arc.
     * @param id Unique identifier of arc.
     * @param source_id The identifier of the source node.
     * @param target_id The identifier of the target node.
     * @param weight The weight of the arc.
     */
    Arc(const std::string& id, const std::string& source_id, const std::string& target_id, int weight = 1);

    /**
     * @brief Gets the unique identifier of the arc.
     */
    std::string getId() const;

    /**
     * @brief Changed the id (but not in petrinet!)
     */
    void setId(std::string new_id);

    /**
     * @brief Gets the unique identifier of the source node.
     */
    std::string getSourceId() const;

    /**
     * @brief Changed the source id (but not in petrinet!)
     */
    void setSourceId(std::string new_id);

    /**
     * @brief Gets the unique identifier of the target node.
     */
    std::string getTargetId() const;

    /**
     * @brief Changed the target id (but not in petrinet!)
     */
    void setTargetId(std::string new_id);

    /**
     * @brief Gets the weight of the arc.
     */
    int getWeight() const;

    /**
     * @brief Sets new weight for the arc.
     * @param weight New value of the weight.
     */
    void setWeight(int weight);

    /**
     * @brief Set the 2D position
     * @param x X-axis position
     * @param y Y-axis position
     */
    void setPosition(float x, float y);

    /**
     * @brief Set the X-axis position
     * @param x value
     */
    void setPosX(float x);

    /**
     * @brief Set the Y-axis position
     * @param y value
     */
    void setPosY(float y);

    /**
     * @brief Get the 2D position
     * @return Pair containing x and y coordinates.
     */
    std::pair<float, float> getPosition() const;
    
private:
    std::string id;
    std::string source_id;
    std::string target_id;
    int weight;
    std::pair<float, float> gui_position;
};