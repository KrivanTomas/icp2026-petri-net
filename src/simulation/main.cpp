/**
 * @file simulation/main.cpp
 *
 * @brief Simulation of the petrinet
 *
 * @author
 *     Lukáš Kurtin
 */


#include <iostream>
#include "../include/petrinet.h"
#include "../include/event.h"

class EventTester : public Observer
{
public:
    virtual void onEvent(Event event, int a) {
        if(event == Event::update_tokens_)
            std::cout << "Got event to update tokens!\n";
        else if(event == Event::fire_)
            std::cout << "Got event to fire!" << a << "\n";
    }
    virtual void onEvent(Event event) {
        if(event == Event::update_tokens_)
            std::cout << "Got event to update tokens!\n";
        else if(event == Event::fire_)
            std::cout << "Got event to fire!\n";
    }
    
};

int main()
{
    std::cout << "Hello from simulation!\n";

    PetriNet p_net = PetriNet();

    p_net.addPlace(Place("1p", 50));
    p_net.addPlace(Place("2p", 4));
    p_net.addPlace(Place("3p", 7));
    p_net.addPlace(Place("4p", 1));
    p_net.addTransition(Transition("1t"));
    p_net.addTransition(Transition("2t"));
    p_net.addTransition(Transition("3t"));
    p_net.addArcs(Arc("1a", "1p", "1t", 2));
    p_net.addArcs(Arc("2a", "1t", "2p", 5));
    p_net.addArcs(Arc("3a", "1t", "3p", 1));

    p_net.addArcs(Arc("4a", "3p", "2t", 2));
    p_net.addArcs(Arc("5a", "2t", "4p", 2));

    p_net.addArcs(Arc("6a", "4p", "1t", 2));

    EventTester* et = new EventTester();

    Sender* sender = new Sender();
    sender->addObserver(et);

    bool fired = true;
    bool manual_fire = 0;
    int counter = 0;
    int fired_count = 0;
    // do{
    //     if(counter == 0) {
    //         fired = p_net.fire("1t");
    //         fired_count++;
    //     }
    //     counter = ((counter+1));
        
    //     std::cin >> manual_fire;

    //     if(fired || manual_fire){
    //         sender->throwEvent(Event::fire_, counter);
    //         fired = false;
    //         manual_fire = false;
    //     }
    // } while(fired_count < 10);

    if(
    p_net.fire("2t") &&
    p_net.fire("2t") &&
    p_net.fire("2t") &&
    p_net.fire("1t") &&
    p_net.fire("1t")
    ) {}else std::cout << "Failed to fire! Check your transition logic.\n";

    // std::cout << (fired ? "Place1 -> Place2 fired successfuly." : "Place1 -> Place2 failed to fire.") << "\n";
    // std::cout << (fired ? "Place1 -> Place3 fired successfuly." : "Place1 -> Place3 failed to fire.") << "\n\n";


    // std::cout << (fired ? "Place1 -> Place2 fired successfuly." : "Place1 -> Place2 failed to fire.") << "\n";
    for(auto& pair : p_net.getPlaces()){
        std::cout << pair.first << " current tokens: " << pair.second.getCurrentTokens() << ".\n";
    }

    return 0;
}
