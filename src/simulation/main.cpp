/**
 * @file main.cpp
 *
 * @brief Simulation of the petrinet
 *
 * @author
 *     Lukáš Kurtin
 */


#include <iostream>
#include "../include/petrinet.h"

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

    std::cout << ((Place)p_net.getPlaces().at(0)).getId() << " current tokens: " << ((Place)p_net.getPlaces().at(0)).getCurrentTokens() << ".\n";
    std::cout << ((Place)p_net.getPlaces().at(1)).getId() << " current tokens: " << ((Place)p_net.getPlaces().at(1)).getCurrentTokens() << ".\n";
    return 0;
}
