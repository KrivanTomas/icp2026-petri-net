Tool for visual editing, code generation, and runtime monitoring of interpreted Petri nets 
Course: ICP

Authors: 
    Tomáš Křivan (xkrivat00) 
    Lukáš Kurtin (xkurtil00) 
    Tomáš Kudera (xkudert00)

Project Description 
The goal was to create an application that allows the user to interact with a visual environment for working with interpreted Petri nets. 
The user has the ability to load or save nets to files, as well as edit and modify them using the graphical environment.

Project Build and Execution
    - Build dependencies: make, cmake, qt5
    - Build command: 'make all'
    - Run command: 'make run'
    - Generate Doxygen documentation: 'make doxygen'

Current implementation status
    - Loading and saving to files in JSON format
    - Editing the petri net places, transitions, arcs and their attributes
    - Basic simulation of nets only with scheduled timers
    - Starting a process simulation from GUI, passing petri net file as an argument
    - Partial simulation side TCP communication maybe?

NOT IMPLEMENTED
    - Robust editor file dirty flags
    - Communication between GUI and simulation
    - Inscryption language support (actions and guard conditions)
    
SIMULATION TESTING
First argument is a path to petri net file.
Simulation was unfortunately not connected to the GUI window. However, it supports very rough tcp communication.
If you run ./simulation; it will begin simulating scheduled transmitions and start looking for an open client at port 20003 to receive data from. 
You can connect through another terminal by using the command "telnet localhost 20003".
You can then write one-word commands in this new terminal, supported are: "help", "exit" and event names.
If, for example, your .json file has transition input events, you can write that event's name into the terminal
and it will try and fire that transition.
Be careful to not close the main application without proper exiting, as the port could become unavailable.
If you do not open the sending terminal, forcefully terminate the program.


Inspiration / Third-party code and libraries
    - json_serialization.h and .cpp files - the open-source C++ library nlohmann/json was used for serialization and deserialization
    - Artificial intelligence was used for the model files to explain implementation details
    - Editor implementation was inspired by: https://doc.qt.io/qt-6/qtwidgets-graphicsview-diagramscene-example.html
    - Simulation's "events" are an implementation of an Observer, inpired by: https://gameprogrammingpatterns.com/observer.html
    - TCP communication was inspired by: https://www.youtube.com/watch?v=cNdlrbZSkyQ
