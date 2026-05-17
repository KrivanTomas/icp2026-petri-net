/**
 * @file simulation/main.cpp
 *
 * @brief Simulation of the petrinet
 *
 * @author
 *     Lukáš Kurtin
 */


#include <iostream>
#include <thread>
#include "../include/petrinet.h"
#include "../include/event.h"
#include "../include/sim_util.h"

PetriNet p_net;
Sender* event_sender = new Sender();

class EventTester : public Observer
{
public:
    EventTester() = default;
    virtual void onEvent(Event event, std::string str) {
        if(event == Event::fire_){
            std::cout << "Got event to fire " << str << "\n";
            //TODO log to GUI
        }
        else {
            std::cout << "IDK what to do with this event: str\n";
        }
    }
    virtual void onEvent(Event event, std::string str, int number) {
        if(event == Event::update_tokens_){
            //std::cout << "Update '" << str << "' tokens by " << number << "\n";
            //TODO update GUI
        }
        else {
            std::cout << "IDK what to do with this event: str, int\n";
        }
    }
    
};

int main()
{
    std::cout << "Hello from simulation!\n";

    SimUtil::setEventSender(event_sender);
    SimUtil::initializeTime();
    
    EventTester* et = new EventTester();
    event_sender->addObserver(et);

    p_net = PetriNet();

    p_net.addPlace(Place("1p", 50));
    p_net.addPlace(Place("2p", 4));
    p_net.addPlace(Place("3p", 7));
    p_net.addPlace(Place("4p", 1));
    p_net.addTransition(Transition("1t"));
    p_net.addTransition(Transition("2t"));
    p_net.addTransition(Transition("3t"));
    p_net.addArc(Arc("1a", "1p", "1t", 2));
    p_net.addArc(Arc("2a", "1t", "2p", 5));
    p_net.addArc(Arc("3a", "1t", "3p", 1));

    p_net.addArc(Arc("4a", "3p", "2t", 2));
    p_net.addArc(Arc("5a", "2t", "4p", 2));

    p_net.addArc(Arc("6a", "4p", "1t", 2));


    int64_t sleep_time;
    bool exit_main_loop = false;

    SimUtil::addTimer("2t", 250);
    SimUtil::addTimer("2t", 40);
    SimUtil::addTimer("2t", 30);
    SimUtil::addTimer("1t", 65);
    SimUtil::addTimer("1t", 50);

    std::cout << "Total timer count: " << SimUtil::scheduled_timers.size() << "\n";
    std::string manual_input = "";
    do{
        sleep_time = 100;
        std::cout << "old time: " << SimUtil::getNetTime() << " ---- new time: ";
        SimUtil::updateTime();
        std::cout << SimUtil::getNetTime() << "\n";
        //listen to tcp
        // if(tcp_updated)
        // {
            
        // }
        // if(external_input){
        //     if(external_input == external_event::exit_)
        //     if(external_input == external_event::fire_)
        // }

        //find time to next transition timeout and fire all elapsed timers
        int64_t timer_lowest_time = SimUtil::checkTimerState(p_net);
        if(timer_lowest_time < sleep_time){
            sleep_time = timer_lowest_time;
        }

        //std::cout << "\n\n" << sleep_time << "\n\n";

        //exiting condition
        if(SimUtil::scheduled_timers.empty()){
            exit_main_loop = true;
        }
        else{   
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        }
    } while(!exit_main_loop);

    //print all place tokens
    for(auto& pair : p_net.getPlaces()){
        std::cout << pair.first << " current tokens: " << pair.second.getCurrentTokens() << ".\n";
    }

    event_sender->removeObserver(et);
    delete et;
    delete event_sender;
    return 0;
}
