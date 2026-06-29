# Discord RPC for Geode 5.7.1

include(FetchContent)

FetchContent_Declare(
    discord_rpc
    GIT_REPOSITORY https://github.com/discord/discord-rpc.git
    GIT_TAG master
)

FetchContent_MakeAvailable(discord_rpc)

target_link_libraries(${PROJECT_NAME} PRIVATE discord-rpc)
