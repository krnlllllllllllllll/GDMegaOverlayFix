# Portable File Dialogs for Geode 5.7.1

include(FetchContent)

FetchContent_Declare(
    pfd
    GIT_REPOSITORY https://github.com/samhocevar/portable-file-dialogs.git
    GIT_TAG master
)

FetchContent_MakeAvailable(pfd)

target_link_libraries(${PROJECT_NAME} PRIVATE portable-file-dialogs)
