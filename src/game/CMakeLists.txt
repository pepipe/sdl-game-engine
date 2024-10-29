# src/game/CMakeLists.txt

add_library(Game Game.cpp)

# include directories for Game
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link SDL
target_link_libraries(Game PRIVATE SDL3::SDL3)