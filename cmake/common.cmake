# Function to set up a game executable
function(setup_game_executable game_name folder_name)
    # Set up source files
    file(GLOB_RECURSE GAME_SRC "${CMAKE_SOURCE_DIR}/src/${folder_name}/*.cpp" "${CMAKE_SOURCE_DIR}/src/${folder_name}/*.h")
    add_executable(${game_name} ${GAME_SRC})

    # Link to GameEngine (you can add more libraries as needed)
    target_link_libraries(${game_name} PRIVATE GameEngine)

    # Set subsystem for Windows
    if (MSVC)
        set_target_properties(${game_name} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
    endif ()

    # Copy assets
    add_custom_command(TARGET ${game_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets/${folder_name}"
            "$<TARGET_FILE_DIR:${game_name}>/assets"
    )

    # Handle DLLs (adjust paths and logic if needed)
    if (WIN32)
        set(SDL_DLL "${CMAKE_SOURCE_DIR}/libs/sdl/release/SDL3.dll")
        set(SDL_IMAGE_DLL "${CMAKE_SOURCE_DIR}/libs/sdl_image/release/SDL3_image.dll")
        set(SDL_MIXER_DLL "${CMAKE_SOURCE_DIR}/libs/sdl_mixer/release/SDL3_mixer.dll")
        set(SDL_TTF_DLL "${CMAKE_SOURCE_DIR}/libs/sdl_ttf/release/SDL3_ttf.dll")

        if (CMAKE_BUILD_TYPE MATCHES Debug)
            set(SDL_DLL "${CMAKE_SOURCE_DIR}/libs/sdl/debug/SDL3.dll")
            set(SDL_IMAGE_DLL "${CMAKE_SOURCE_DIR}/libs/sdl_image/debug/SDL3_image.dll")
            set(SDL_MIXER_DLL "${CMAKE_SOURCE_DIR}/libs/sdl_mixer/debug/SDL3_mixer.dll")
            set(SDL_TTF_DLL "${CMAKE_SOURCE_DIR}/libs/sdl_ttf/debug/SDL3_ttf.dll")
        endif ()

        add_custom_command(TARGET ${game_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL_DLL}"
                "$<TARGET_FILE_DIR:${game_name}>/SDL3.dll"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL_IMAGE_DLL}" # Path to SDL dll
                "$<TARGET_FILE_DIR:${game_name}>/SDL3_image.dll" # Output directory
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL_MIXER_DLL}"
                "$<TARGET_FILE_DIR:${game_name}>/SDL3_mixer.dll"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL_TTF_DLL}"
                "$<TARGET_FILE_DIR:${game_name}>/SDL3_ttf.dll"
        )
    endif ()
endfunction()