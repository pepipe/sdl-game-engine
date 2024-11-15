# src/game-pong/CMakeLists.txt
setup_game_executable(PongGame game-pong)

# include directories for PongGame
target_include_directories(PongGame PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/events
        ${CMAKE_CURRENT_SOURCE_DIR}/objects
        ${CMAKE_CURRENT_SOURCE_DIR}/score
)