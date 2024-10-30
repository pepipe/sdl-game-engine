# src/CMakeLists.txt

# Add subdirectories
add_subdirectory(game-engine)

# Define the executable
add_executable (SDLEngine "main.cpp")

# Link SDL3 Library
target_link_libraries(SDLEngine PRIVATE SDL3::SDL3 GameEngine)

# Copy SDL3.dll to the output directory after build
if(WIN32)
    # Default to the Release DLL unless the build type is Debug
    set(SDL_DLL "$ENV{SDL3_DIR}/bin/SDL3.dll")

    if(CMAKE_BUILD_TYPE MATCHES Debug)
        set(SDL_DLL "$ENV{SDL3_DIR}/bin/SDL3d.dll")  # Debug DLL
    endif()
    
    add_custom_command(TARGET SDLEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL_DLL}" # Path to SDL dll
            "$<TARGET_FILE_DIR:SDLEngine>/SDL3.dll"              # Output directory
    )
endif()
