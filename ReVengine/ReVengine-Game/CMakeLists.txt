add_executable(ReVengine-Game "Game.cpp") #No need to add header files

target_link_libraries(ReVengine-Game ReVengine-Engine) #links Game to Engine lib(dll)

set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resources")

add_custom_target(copy_game_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCES_DIR}"
        "${CMAKE_BINARY_DIR}/game_resources"
    COMMENT "Copying resources to build directory"
)

# add this as a dependency to the game
add_dependencies(ReVengine-Game copy_game_resources)