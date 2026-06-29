# Git metadata for Geode 5.7.1 builds

find_package(Git QUIET)

if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    set(GIT_COMMIT "unknown")
endif()

set(GEODE_GIT_COMMIT "${GIT_COMMIT}" PARENT_SCOPE)
