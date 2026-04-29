/**
 * @file place.h
 *
 * @brief Header file for places
 *
 * @author
 *     Tomáš Kudera
 */


#pragma once

#include <string>

/**
* @class Place
* @brief Class that represents a place in Petri net where are tokens
*/
class Place
{
public:
    /**
     * @brief Constructor for Place.
     * @param id Identifier of the place.
     * @param token_count Number of tokens (default value is 0).
     */
    Place(const std::string& id, int initial_tokens = 0);

    /**
     * @brief Gets unique identifier of the place.
     */
    std::string getId();

    /**
     * @brief Gets initial number of tokens.
     */
    int getInitialTokens();

    /**
     * @brief Sets new value for number of initial tokens.
     * @param count Number of tokens.
     */
    void setInitialTokens(int count);

    /**
     * @brief Gets number of current tokens.
     */
    int getCurrentTokens();

    /**
     * @brief Sets new number of current tokens.
     * @param count Number of tokens.
     */
    void setCurrentTokens(int count);

    /**
     * @brief Gets the action code. 
     */
    std::string getActionCode();

    /**
     * @brief Sets action code asssociated with this place.
     * @param code String containig code.
     */
    void setActionCode(const std::string& code);

private:
    std::string m_id;
    int m_initial_tokens;
    int m_current_tokens;
    std::string m_action_code;
};
