/**
 * @file sim_util.h
 *
 * @brief Utility for simulation definition
 *
 * @author
 *     Lukáš Kurtin
 */

#pragma once

#include "petrinet.h"
#include "event.h"

class SimUtil{
public:

    /**
     * @brief Function checks if transition has enough tokens to be fired.
     * @param transition_id ID of transition, that is checked.
     * @return True, if transition can be fired, or false if can not.
    */
    static bool ableToBeFired(PetriNet& pnet, const std::string& transition_id);

    /**
     * @brief Function fires transition, fires token_change_ events.
     * @param transition_id ID of transition.
     * @return True if transition was safely fired, else false.
     */
    static bool fire(PetriNet& pnet, const std::string& transition_id);

    /**
     * @brief Checks all scheduled timers and fires their transition if any have elapsed.
     * 
     * Also returns the lowest time until next timer elapses.
     * @param pnet Petri net
     * @return Time to next timer elapse
     */
    static int64_t evaluateTimerState(PetriNet& pnet);

    /**
     * @brief Gets the event sender of this object
     * @return The sender object
     */
    static Sender* getEventSender();

    /**
     * @brief Sets the event_sender, which fires events inside this class' functions.
     * @param sender Sender to set
     */
    static void setEventSender(Sender* sender);

    /**
     * @brief Creates a scheduled timer
     * @param trans_id Id of transition
     * @param time Time in milliseconds
     */
    static void addTimer(std::string trans_id, int64_t time);

    /**
     * @brief Updates current internal time. (Milliseconds since launch).
     */
    static void updateTime();

        /**
     * @brief Returns current time of the petri net.
     * @return Time in milliseconds.
     */
    static int getNetTime();

    /**
     * @brief Returns current system time.
     * @return Time in milliseconds.
     */
    static int64_t getSystemTime();

    /**
     * @brief Initialize starting internal timer value
     */
    static void initializeTime();

    static std::map<std::pair<std::string, int32_t>, int64_t> scheduled_timers;
    
private:
    static Sender* event_sender;

    static int64_t time_at_start;
    static int64_t current_time_ms;
    static uint32_t timer_index_counter;
};