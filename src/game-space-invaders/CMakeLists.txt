# src/game-space-invaders/CMakeLists.txt
setup_game_executable(SpaceInvadersGame game-space-invaders)

# include directories for PongGame
target_include_directories(SpaceInvadersGame PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/events
        ${CMAKE_CURRENT_SOURCE_DIR}/objects
)