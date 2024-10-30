# src/game-engine/CMakeLists.txt

file(GLOB GAME_ENGINE_SRC "*.cpp")
add_library(GameEngine STATIC ${GAME_ENGINE_SRC})

# include directories for Game
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link SDL
target_link_libraries(GameEngine PRIVATE SDL3::SDL3)
#target_link_libraries(Game PRIVATE SDL3_image::SDL3_image)