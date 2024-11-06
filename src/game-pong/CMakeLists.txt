# src/game-pong/CMakeLists.txt

# Define the executable
file(GLOB_RECURSE PONG_SRC "*.cpp" "*.h")
add_executable (PongGame ${PONG_SRC})

# Link SDL3 Library
target_link_libraries(PongGame PRIVATE GameEngine SDL3)

# Set the subsystem for Windows (only necessary for executables)
if(MSVC)
    set_target_properties(PongGame PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

# Copying assets
add_custom_command(TARGET PongGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets/game-pong" # Source directory
        "$<TARGET_FILE_DIR:PongGame>/assets" # Destination directory
)

# Copy SDL3.dll to the output directory after build (windows specific)
if(WIN32)
    # Default to the Release DLL unless the build type is Debug
    set(SDL_DLL "${CMAKE_SOURCE_DIR}/sdk/sdl/release/SDL3.dll")   # Release DLL
    set(SDL_MIXER_DLL "${CMAKE_SOURCE_DIR}/sdk/sdl_mixer/release/SDL3_mixer.dll")
    set(SDL_TTF_DLL "${CMAKE_SOURCE_DIR}/sdk/sdl_ttf/release/SDL3_ttf.dll")
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        set(SDL_DLL "${CMAKE_SOURCE_DIR}/sdk/sdl/debug/SDL3.dll")  # Debug DLL
        set(SDL_MIXER_DLL "${CMAKE_SOURCE_DIR}/sdk/sdl_mixer/debug/SDL3_mixer.dll")
        set(SDL_TTF_DLL "${CMAKE_SOURCE_DIR}/sdk/sdl_ttf/debug/SDL3_ttf.dll")
    endif()

    add_custom_command(TARGET PongGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL_DLL}" # Path to SDL dll
            "$<TARGET_FILE_DIR:PongGame>/SDL3.dll" # Output directory
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL_MIXER_DLL}" # Path to SDL dll
            "$<TARGET_FILE_DIR:PongGame>/SDL3_mixer.dll" # Output directory
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL_TTF_DLL}" # Path to SDL dll
            "$<TARGET_FILE_DIR:PongGame>/SDL3_ttf.dll" # Output directory
    )
endif()