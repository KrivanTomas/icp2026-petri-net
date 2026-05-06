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


int main()
{
    std::cout << "Hello from simulation!\n";

    PetriNet p_net = PetriNet();

    p_net.addPlace(Place("1p", 8));
    p_net.addPlace(Place("2p", 4));
    p_net.addTransition(Transition("1t"));
    p_net.addArcs(Arc("1a", "1p", "1t", 2));
    p_net.addArcs(Arc("2a", "1t", "2p", 5));

    
    bool fired = p_net.fire("1t");
    

    std::cout << (fired ? "Place1 -> Place2 fired successfuly." : "Place1 -> Place2 failed to fire.") << "\n";

    std::cout << "1p current tokens: " << p_net.getPlaces().at("1p").getCurrentTokens() << ".\n";
    std::cout << "2p current tokens: " << p_net.getPlaces().at("2p").getCurrentTokens() << ".\n";
    return 0;
}
