# src/CMakeLists.txt
# Authors:
#   Tomáš Křivan

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# c/c++ header files
include_directories(./include)

# Qt gui xml files
include_directories(./ui)



add_library(module_test OBJECT
    module_test.cpp 
    include/module_test.h
)


# Petri net model
add_library(net_model OBJECT
    model/petrinet.cpp 
    model/place.cpp 
    model/transition.cpp
    model/arc.cpp 
    include/petrinet.h 
    include/place.h 
    include/transition.h 
    include/arc.h
)
target_link_libraries(net_model 
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
)

add_library(editor OBJECT
    editor/editor_graphics_scene.cpp 
    include/editor_graphics_scene.h 

    editor/editor_node.cpp 
    include/editor_node.h 

    editor/editor_place_item.cpp 
    include/editor_place_item.h 

    editor/editor_transition_item.cpp 
    include/editor_transition_item.h 

    editor/editor_arc_item.cpp 
    include/editor_arc_item.h 

    editor/place_property_editor.cpp
    include/place_property_editor.h
    ui/place_property_editor.ui

    editor/transition_property_editor.cpp
    include/transition_property_editor.h
    ui/transition_property_editor.ui

    editor/arc_property_editor.cpp
    include/arc_property_editor.h
    ui/arc_property_editor.ui
)
target_link_libraries(editor 
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
)

add_library(main_window OBJECT
    main_window.cpp 
    include/main_window.h 
    ui/main_window.ui
)
target_link_libraries(main_window 
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
)



add_executable(main 
    main.cpp
)
target_link_libraries(main 
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets module_test main_window net_model editor
)


# set main binary location to ./build/main instead of ./build/src/main
set_target_properties(main 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
