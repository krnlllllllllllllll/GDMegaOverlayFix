# Subprocess for Geode 5.7.1

include(FetchContent)

FetchContent_Declare(
    subprocess
    GIT_REPOSITORY https://github.com/benhoyt/subprocess.git
    GIT_TAG master
)

FetchContent_MakeAvailable(subprocess)

target_link_libraries(${PROJECT_NAME} PRIVATE subprocess)
