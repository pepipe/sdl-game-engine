# src/game-engine/CMakeLists.txt

file(GLOB GAME_ENGINE_SRC "*.cpp")
file(GLOB PHYSICS_SRC "physics/*.cpp")
add_library(GameEngine STATIC ${GAME_ENGINE_SRC} ${PHYSICS_SRC})

# include directories for GameEngine
target_include_directories(GameEngine PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/physics
)

# Link SDL
target_link_libraries(GameEngine PRIVATE SDL3::SDL3)
#target_link_libraries(Game PRIVATE SDL3_image::SDL3_image)