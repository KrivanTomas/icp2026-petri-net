#include "../src/include/petrinet.h"
#include <gtest/gtest.h>

TEST(Structure, AddingUniqueAndDupliciteNodes) {
    PetriNet test_structure;
    EXPECT_TRUE(test_structure.addPlace(Place("P1", 5)));
    EXPECT_TRUE(test_structure.addTransition(Transition("T1")));

    EXPECT_FALSE(test_structure.addPlace(Place("P1", 5)));
    EXPECT_FALSE(test_structure.addTransition(Transition("T1")));
}

TEST(Structure, BipartiteGraph) {
    PetriNet test_net;
    test_net.addPlace(Place("P1"));
    test_net.addPlace(Place("P2"));

    test_net.addTransition(Transition("T1"));
    test_net.addTransition(Transition("T2"));

    EXPECT_TRUE(test_net.addArc(Arc("A1", "P1", "T1")));
    EXPECT_TRUE(test_net.addArc(Arc("A2", "T1", "P2")));

    EXPECT_FALSE(test_net.addArc(Arc("A3", "P1", "P2")));
    EXPECT_FALSE(test_net.addArc(Arc("A4", "T1", "T2")));
    EXPECT_FALSE(test_net.addArc(Arc("A5", "kudy", "P2")));
}

TEST(Data, InputsVariables) {
    PetriNet test_net;

    EXPECT_FALSE(test_net.isInputDefined("condition"));

    test_net.setInputValue("condition", "3524165");
    test_net.setVariable("timeout", "100");

    EXPECT_TRUE(test_net.isInputDefined("condition"));
    EXPECT_EQ(test_net.getInputValue("condition"), "3524165");
    EXPECT_EQ(test_net.getVariable("timeout"), "100");
}
