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



add_library(module_test 
    module_test.cpp 
    include/module_test.h
)


add_library(main_window 
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
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets module_test main_window
)


# set main binary location to ./build/main instead of ./build/src/main
set_target_properties(main 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
