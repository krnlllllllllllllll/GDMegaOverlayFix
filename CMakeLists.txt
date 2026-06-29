cmake_minimum_required(VERSION 3.21)

project(GDMegaOverlayFix LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable IDE folder grouping
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Fetch Geode SDK
include(FetchContent)
FetchContent_Declare(
    geode
    GIT_REPOSITORY https://github.com/geode-sdk/geode.git
    GIT_TAG v5.7.1
)
FetchContent_MakeAvailable(geode)

# Define your mod metadata
geode_mod(
    ID "krn.gdmegaoverlayfix"
    NAME "GDMegaOverlayFix"
    VERSION "1.0.0"
    DESCRIPTION "Fixes Mega Overlay behavior in Geometry Dash"
    AUTHOR "krn"
)

# Add your source files
file(GLOB_RECURSE MOD_SOURCES
    src/*.cpp
    src/*.c
    src/*.hpp
    src/*.h
)

add_library(${PROJECT_NAME} SHARED ${MOD_SOURCES})

# Link Geode
target_link_libraries(${PROJECT_NAME} geode)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Build the final .geode package
geode_add_mod(${PROJECT_NAME})
