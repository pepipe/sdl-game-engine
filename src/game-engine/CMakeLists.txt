# src/game-engine/CMakeLists.txt

add_library(GameEngine STATIC GameEngine.cpp GameObjectManager.cpp)

# include directories for Game
target_include_directories(GameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link SDL
target_link_libraries(GameEngine PRIVATE SDL3::SDL3)
#target_link_libraries(Game PRIVATE SDL3_image::SDL3_image)