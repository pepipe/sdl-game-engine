# src/CMakeLists.txt

# Add subdirectories
add_subdirectory(Game)

# Define the executable
add_executable (DeathRunSDL "DeathRunSDL.cpp")

# Link SDL3 Library
target_link_libraries(DeathRunSDL PRIVATE SDL3::SDL3 Game)

# Copy SDL3.dll to the output directory after build
if(WIN32)
    add_custom_command(TARGET DeathRunSDL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/libs/SDL/SDL3.dll"  # Path to SDL3.dll
            "$<TARGET_FILE_DIR:DeathRunSDL>"              # Output directory
    )
endif()
