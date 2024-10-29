# src/CMakeLists.txt

# Add subdirectories
add_subdirectory(Game)

# Define the executable
add_executable (DeathRunSDL "DeathRunSDL.cpp")

# Link SDL3 Library
target_link_libraries(DeathRunSDL PRIVATE Game SDL3::SDL3)

# Copy SDL3.dll to the output directory after build
if(WIN32)
     # Default to the Release DLL unless the build type is Debug
    set(SDL_DLL "${SDL3_DIR}/Release/SDL3.dll")

    if(CMAKE_BUILD_TYPE MATCHES Debug)
        set(SDL_DLL "${SDL3_DIR}/Debug/SDL3.dll")  # Debug DLL
    endif()

    add_custom_command(TARGET DeathRunSDL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL_DLL}"   # Path to SDL3.dll
            "$<TARGET_FILE_DIR:DeathRunSDL>/SDL3.dll"  # Output directory
    )
endif()