# CMakeLists.txt
# Authors:
#   Tomáš Křivan

cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

project(
    icp2026-petri-net
    VERSION 0.0
    DESCRIPTION "Petri net editor and simulator"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")

set(QT_VERSION_MAJOR 5)

# for neovim and other editors
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_subdirectory(src)
