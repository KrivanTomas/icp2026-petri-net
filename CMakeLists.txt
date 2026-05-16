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

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(nlohmann_json)

# tests
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0    
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests tests/tests_model.cpp)

target_link_libraries(run_tests PRIVATE net_model gtest_main)

include(GoogleTest)

gtest_discover_tests(run_tests)
