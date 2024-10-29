# src/CMakeLists.txt

# Add subdirectories
add_subdirectory(Game)

# Define the executable
add_executable (DeathRunSDL "DeathRunSDL.cpp")

# Link SDL3 Library
target_link_libraries(DeathRunSDL PRIVATE Game SDL3::SDL3-static)