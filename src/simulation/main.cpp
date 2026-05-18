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

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include <cstring>
#include "../include/petrinet.h"
#include "../include/event.h"
#include "../include/sim_util.h"
#include "../include/json_serializer.h"

PetriNet p_net;
Sender* event_sender = new Sender();

//variables for thread communication (events)
bool exit_main_loop = false;
std::string fire_event_name = "";
int client_socket;

class EventListener : public Observer
{
public:
    EventListener() = default;

    virtual void onEvent(Event event, std::string str) {
        if(event == Event::fire_){
            std::cout << "Fired transition " << str << "\n";

            for(auto& pair : p_net.getPlaces()){
                std::cout << pair.first << " current tokens: " << pair.second.getCurrentTokens() << ".\n";
            }
            //TODO log to GUI
        }
        else if(event == Event::timer_ignored_){
            std::cout << "Transition could not be fired. Check source place tokens.\n";
            //TODO log to GUI   //timeout ignored
        }
    }
    virtual void onEvent(Event event, std::string str, int number) {
        str = str;
        number = number;
        if(event == Event::update_tokens_){
            //std::cout << "Update '" << str << "' tokens by " << number << "\n";
            //TODO update GUI
        }
        else {
            std::cout << "IDK what to do with this event: str, int\n";
        }
    }
    
};

void communicate(){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1){
        std::cout << "Socket could not be created.\n";
        return;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(20003);
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

    if(bind(server_socket, (sockaddr*)&hint, sizeof(hint)) == -1){
        std::cout << "Couldnt bind the address\n";
        return;
    }

    if(listen(server_socket, SOMAXCONN) == -1){
        std::cout << "Listening error\n";
        return;
    }

    sockaddr_in client;
    socklen_t client_size = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int client_socket = accept(server_socket, (sockaddr*)&client, &client_size);
    if(client_socket == -1){
        std::cout << "Couldnt connect to client\n";
        return;
    }

    close(server_socket);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);
    if(result){
        std::cout << "Connected\n";
    }
    else{
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << "Connected\n";
    }

    char buf[4096];
    while(true){
        memset(buf, 0, 4096);
        int bytes_received = recv(client_socket, buf, 4096, 0);
        if(bytes_received == -1){
            std::cout << "Connection issue\n";
            break;
        }
        if(bytes_received == 0){
            std::cout << "Client disconnected\n";
            break;
        }

        if(std::string(buf, 0, bytes_received-2) == "exit"){
            exit_main_loop = true;
            break;
        }
        else if(std::string(buf, 0, bytes_received-2) == "help"){
            std::cout << "Help:\nNapiste jmeno eventu pro jeho vyvolani.\
            \nPrikazem 'exit' ukoncite zapis, program ceka na uplynuti casovanych odpalu a ukonci se.\
            \nVzdy po vypaleni prechodu vypise novy stav vsech mist.\n\n";
        }
        else {
            fire_event_name = std::string(buf, 0, bytes_received-2);
        }
    }
    //client_socket closes in main function
}

/**
 * @brief Entry point of simulation
 */
int main(int argc, char** argv)
{
    std::string json_file_name = "../examples/example1.json";
    if(argc >= 2){
        json_file_name = argv[1];
    }

    bool enable_debug_output = false;

    SimUtil::setEventSender(event_sender);
    SimUtil::initializeTime();
    
    EventListener* listener = new EventListener();
    event_sender->addObserver(listener);

    //read petri net from file
    std::string read_failure = "JSON was read correctly";
    if(!JsonSerializer::loadFile(json_file_name, p_net, read_failure)){
        std::cout << read_failure << "\n";
        return 1;
    }
    else {
        if(enable_debug_output)
            std::cout << "File loaded succesfully\n";
    }

    int64_t sleep_time;


    //initiate timers for non-negative delay values
    for(auto pair : p_net.getTransitions()) {
        if(pair.second.getDelay() >= 0){
            //set scheduled timeout
            SimUtil::addTimer(pair.first, pair.second.getDelay());
        }
    }

    std::thread t_comm(communicate);

    do{
        sleep_time = 500;
        if(enable_debug_output)
            std::cout << "old time: " << SimUtil::getNetTime() << " ---- new time: ";

        //snapshot current time
        SimUtil::updateTime();

        if(enable_debug_output)
            std::cout << SimUtil::getNetTime() << "\n";


        //find time to next transition timeout and fire all elapsed timers
        int64_t timer_lowest_time = SimUtil::evaluateTimerState(p_net, fire_event_name);

        if(timer_lowest_time < sleep_time){
            sleep_time = timer_lowest_time;
        }
 
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    } while(!exit_main_loop);

    t_comm.join();
    close(client_socket);

    //print all place tokens
    //if(enable_debug_output)
        for(auto& pair : p_net.getPlaces()){
            std::cout << pair.first << " current tokens: " << pair.second.getCurrentTokens() << ".\n";
        }

    //uncomment this to save file (for testing purposes); 
    // ---!! OVERRIDES INPUT FILE !!---
    //JsonSerializer::saveFile(json_file_name, p_net, read_failure);


    event_sender->removeObserver(listener);
    delete listener;
    delete event_sender;
    return 0;
}
