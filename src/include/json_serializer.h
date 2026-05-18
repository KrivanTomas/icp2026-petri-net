/**
 * @file json_serializer.h
 *
 * @brief Header file of json serialization.
 *
 * @author
 *     Tomáš Kudera
 */

#pragma once

#include <string>
#include "petrinet.h"


/**
 * @brief Loads and saves Petri net and network descriptor as JSON files.
 */
class JsonSerializer {
public:
    /**
     * @brief Function loads Petri net from a JSON file.
     * @param file Name or path to the file.
     * @param petri_net Petri net.
     * @param error_msg Message on failure. 
     * @return True if load was succesful, or false if not.
     */
    static bool loadFile(const std::string& file, PetriNet& petri_net, std::string& error_msg);

    /**
     * @brief Function saves Petri net into the JSON file.
     * @param file Name or path to the file.
     * @param petri_net Petri net.
     * @param error_msg Message on failure. 
     * @return True if save was succesful, or false if not.
     */
    static bool saveFile(const std::string& file, PetriNet& petri_net, std::string& error_msg);
};
