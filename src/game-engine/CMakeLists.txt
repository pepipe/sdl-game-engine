# src/game-engine/CMakeLists.txt

file(GLOB_RECURSE GAME_ENGINE_SRC "*.cpp" "*.h")
add_library(GameEngine STATIC ${GAME_ENGINE_SRC})

# include directories for GameEngine
target_include_directories(GameEngine PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/math
        ${CMAKE_CURRENT_SOURCE_DIR}/objects
        ${CMAKE_CURRENT_SOURCE_DIR}/physics
        ${CMAKE_CURRENT_SOURCE_DIR}/utilities
)

# Link SDL
target_link_libraries(GameEngine PRIVATE SDL3)
target_link_libraries(GameEngine PRIVATE SDL3_mixer)