cmake_minimum_required(VERSION 3.21)
project(GDMegaOverlayFix)

# Use C++20 (Geode 5.7.1 requires modern C++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Include Geode SDK
include(FetchContent)
FetchContent_Declare(
    geode
    GIT_REPOSITORY https://github.com/geode-sdk/geode.git
    GIT_TAG v5.7.1
)
FetchContent_MakeAvailable(geode)

# Include your
