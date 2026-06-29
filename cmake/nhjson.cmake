# NHJSON for Geode 5.7.1

include(FetchContent)

FetchContent_Declare(
    nhjson
    GIT_REPOSITORY https://github.com/SpaghettDev/nhjson.git
    GIT_TAG main
)

FetchContent_MakeAvailable(nhjson)

target_link_libraries(${PROJECT_NAME} PRIVATE nhjson)
