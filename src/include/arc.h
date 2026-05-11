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
     * @brief Gets the unique identifier of the source node.
     */
    std::string getSourceId() const;

    /**
     * @brief Gets the unique identifier of the target node.
     */
    std::string getTargetId() const;

    /**
     * @brief Gets the weight of the arc.
     */
    int getWeight() const;

    /**
     * @brief Sets new weight for the arc.
     * @param weight New value of the weight.
     */
    void setWeight(int weight);

private:
    std::string m_id;
    std::string m_source_id;
    std::string m_target_id;
    int m_weight;
};