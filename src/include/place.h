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
    std::string getId() const;

    /**
     * @brief Changed the id (but not in petrinet!)
     */
    void setId(std::string new_id);

    /**
     * @brief Gets initial number of tokens.
     */
    int getInitialTokens() const;

    /**
     * @brief Sets new value for number of initial tokens.
     * @param count Number of tokens.
     */
    void setInitialTokens(int count);

    /**
     * @brief Gets number of current tokens.
     */
    int getCurrentTokens() const;

    /**
     * @brief Sets new number of current tokens.
     * @param count Number of tokens.
     */
    void setCurrentTokens(int count);

    /**
     * @brief Gets the action code. 
     */
    std::string getActionCode() const;

    /**
     * @brief Sets action code asssociated with this place.
     * @param code String containig code.
     */
    void setActionCode(const std::string& code);

    /**
     * @brief Gets the last timestamp when place was changed.
     */
    int getLastTimeChange() const;

    /**
     * @brief Sets the last time stamp when place was changed.
     * @param time_ms Time of change in ms.
     */
    void setLastTimeChange(int64_t time_ms);

private:
    std::string id;
    int initial_tokens;
    int current_tokens;
    std::string action_code;
    int64_t last_change_time_ms = 0;
};
