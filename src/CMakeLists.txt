# src/CMakeLists.txt
# Authors:
#   Tomáš Křivan

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(module_test module_test.cpp module_test.h)

add_library(main_window main_window.cpp main_window.h main_window.ui)
target_link_libraries(main_window PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets module_test main_window)
