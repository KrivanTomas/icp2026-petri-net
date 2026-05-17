/**
 * @file file_management.cpp
 *
 * @brief Header file of json serialization.
 *
 * @author
 *     Tomáš Kudera
 */
#pragma once

#include <string>
#include <vector>
#include "petrinet.h"

/**
 * @struct descriptor
 * @brief Metadata that are not stored in PetriNet itself.
 */
struct descriptor {
    std::string name;
    std::string comment;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
    std::vector<std::string> variables;
};

/**
 * @brief Loads and saves Petri net and network descriptor as JSON files.
 */
class JsonSerializer {
public:
    /**
     * @brief Function loads Petri net from a JSON file.
     * @param file Name or path to the file.
     * @param petri_net Petri net.
     * @param net_descriptor Descriptor of the network.
     * @param error_msg Message on failure. 
     * @return True if load was succesful, or false if not.
     */
    static bool loadFile(const std::string& file, PetriNet& petri_net, descriptor& net_descriptor, std::string& error_msg);

    /**
     * @brief Function saves Petri net into the JSON file.
     * @param file Name or path to the file.
     * @param petri_net Petri net.
     * @param net_descriptor Descriptor of the network.
     * @param error_msg Message on failure. 
     * @return True if save was succesful, or false if not.
     */
    static bool saveFile(const std::string& file, PetriNet& petri_net, const descriptor& net_descriptor, std::string& error_msg);
};
