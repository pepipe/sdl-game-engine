# src/game-pong/CMakeLists.txt

# Define the executable
file(GLOB PONG_SRC "*.cpp")
add_executable (PongGame ${PONG_SRC})

# Link SDL3 Library
target_link_libraries(PongGame PRIVATE GameEngine SDL3::SDL3)

# Set the subsystem for Windows (only necessary for executables)
if(MSVC)
    set_target_properties(PongGame PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

# Copy SDL3.dll to the output directory after build (windows specific)
if(WIN32)
    # Default to the Release DLL unless the build type is Debug
    set(SDL_DLL "${CMAKE_SOURCE_DIR}/sdk/sdl/windows/SDL3.dll")

    if(CMAKE_BUILD_TYPE MATCHES Debug)
        set(SDL_DLL "${CMAKE_SOURCE_DIR}/sdk/sdl/windows/SDL3d.dll")  # Debug DLL
    endif()

    add_custom_command(TARGET PongGame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL_DLL}" # Path to SDL dll
            "$<TARGET_FILE_DIR:PongGame>/SDL3.dll"              # Output directory
    )
endif()