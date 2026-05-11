/**
 * @file file_management.cpp
 *
 * @brief Implementation of json serialization.
 *
 * @author
 *     Tomáš Kudera
 */

#include "include/file_management.h"
#include "nlohmann/json.hpp"

#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

/**
 * @brief Function reads a JSON string field.
 */
static std::string jsonToString(const json& object, const std::string& key, const std::string& fallback = "") {
    if(object.contains(key) && object[key].is_string()) {
        return object[key].get<std::string>();
    }
    return fallback;
}

/**
 * @brief Function reads a JSON integer field with default fallback.
 */
static int jsonToInteger(const json& object, const std::string& key, int fallback = 0) {
    if(object.contains(key) && object[key].is_number_integer()) {
        return object[key].get<int>();
    }
    return fallback;
}

bool JsonSerializer::loadFile(const std::string& file, PetriNet& petri_net, descriptor& net_descriptor, std::string& error_msg) {
    std::ifstream input_file(file);
    if(!input_file.is_open()) {
        error_msg = "Cannot open file: " + file;
        return false;
    }

    //parsing JSON
    json jsn;
    try {
        input_file >> jsn;
    }
    catch(const json::parse_error& ex) {
        error_msg = std::string("JSON parse error: ") + ex.what();
        return false;
    }

    //extraction of name and comment information from network
    net_descriptor.name = jsonToString(jsn, "name");
    net_descriptor.comment = jsonToString(jsn, "comment");

    //extraction of inputs
    net_descriptor.inputs.clear();
    if(jsn.contains("inputs") && jsn["inputs"].is_array()) {
        for(const auto& input : jsn["inputs"]) {
            if(input.is_string()) {
                net_descriptor.inputs.push_back(input.get<std::string>());
            }
        }
    }
    
    //extraction of declared outputs
    net_descriptor.outputs.clear();
    if(jsn.contains("outputs") && jsn["outputs"].is_array()) {
        for(const auto& output : jsn["outputs"]) {
            if(output.is_string()) {
                net_descriptor.outputs.push_back(output.get<std::string>());
            }
        }
    }

    //extraction of declared variables
    net_descriptor.variables.clear();
    if(jsn.contains("variables") && jsn["variables"].is_array()) {
        for(const auto& var : jsn["variables"]) {
            if(var.is_string()) {
                net_descriptor.variables.push_back(var.get<std::string>());
            }
        }
    }

    //sync of name and comment into instance of petri net
    petri_net.setName(net_descriptor.name);
    petri_net.setComment(net_descriptor.comment);

    //iteration over array and construction of Place objects
    if(jsn.contains("places") && jsn["places"].is_array()) {
        for(const auto& place_jsn : jsn["places"]) {
            std::string id = jsonToString(place_jsn, "id");
            int init_tokens = jsonToInteger(place_jsn, "initial_tokens", 0);
            std::string action_code = jsonToString(place_jsn, "action_code");

            if(id.empty()) {
                error_msg = "Place entry is missing id.";
                return false;
            }

            Place place(id, init_tokens);
            place.setActionCode(action_code);

            if(!petri_net.addPlace(place)) {
                error_msg = "Duplicite id of places: " + id;
                return false;
            }
        }
    }

    
    //iteration over array and construction of Transition objects
    if(jsn.contains("transitions") && jsn["transitions"].is_array()) {
        for(const auto& trans_jsn : jsn["transitions"]) {
            std::string id = jsonToString(trans_jsn, "id");
            std::string input_event = jsonToString(trans_jsn, "input_event");
            std::string guard = jsonToString(trans_jsn, "guard");
            int delay_ms = jsonToInteger(trans_jsn, "delay_ms", 0);
            std::string action_code = jsonToString(trans_jsn, "action_code");

            if(id.empty()) {
                error_msg = "Transition is missing an id.";
                return false;
            }

            Transition trans(id);
            trans.setInputEventName(input_event);
            trans.setGuardCondition(guard);
            trans.setDelay(delay_ms);
            trans.setActionCode(action_code);

            if(!petri_net.addTransition(trans)) {
                error_msg = "Duplicate transition id: " + id;
                return false;
            }
        }
    }

    
    //iteration over array and construction of Arc objects
    if(jsn.contains("arcs") && jsn["arcs"].is_array()) {
        for(const auto& arc_jsn : jsn["arcs"]) {
            std::string id = jsonToString(arc_jsn, "id");
            std::string source = jsonToString(arc_jsn, "source");
            std::string target = jsonToString(arc_jsn, "target");
            int weight = jsonToInteger(arc_jsn, "weight", 1);

            if(id.empty() || source.empty() || target.empty()) {
                error_msg = "Arc is missing 'id', 'source' or 'target'.";
                return false;
            }

            Arc arc(id, source, target, weight);
            if(!petri_net.addArcs(arc)) {
                error_msg = "Duplicate or invalid arc - id: " + id + ", source: " + source + ", target: " + target;
                return false;
            }
        }
    }
    return true;
}

bool JsonSerializer::saveFile(const std::string& file, const PetriNet& petri_net,const descriptor& net_descriptor, std::string& error_msg) {
    json jsn;
    //descriptor
    jsn["name"] = net_descriptor.name;
    jsn["comment"] = net_descriptor.comment;
    jsn["inputs"] = net_descriptor.inputs;
    jsn["outputs"] = net_descriptor.outputs;
    jsn["variables"] = net_descriptor.variables;

    //serialazation of all places
    jsn["places"] = json::array();
    for(const auto& [id, place] : petri_net.getPlaces()) {
        jsn["places"].push_back({
            {"id", place.getId() },
            {"initial_tokens", place.getInitialTokens()},
            {"action_code", place.getActionCode()}
        });
    }

    //serialazation of all transitions
    jsn["transitions"] = json::array();
    for(const auto& [id, trans] : petri_net.getTransitions()) {
        jsn["transitions"].push_back({
            {"id", trans.getId() },
            {"input_event", trans.getInputEventName()},
            {"guard", trans.getGuardcondition()},
            {"delay_ms", trans.getDelay()},
            {"action_code", trans.getActionCode()}
        });
    }

    //serialazation of all arcs
    jsn["arcs"] = json::array();
    for(const auto& [id, arc] : petri_net.getArcs()) {
        jsn["arcs"].push_back({
            {"id", arc.getId() },
            {"source", arc.getSourceId()},
            {"target", arc.getTargetId()},
            {"weight", arc.getWeight()}
        });
    }

    std::ofstream output_file(file);
    if(!output_file.is_open()) {
        error_msg = "Failed to open output file: " + file;
        return false;
    }

    try {
        output_file << jsn.dump(4);
    }
    catch(const std::exception& ex) {
        error_msg = std::string("JSON write error: ") + ex.what();
        return false;
    }

    return true;
}