# Root CMakeLists.txt : CMake project for SDLEngine
cmake_minimum_required(VERSION 3.8)

project("SDLEngine")

# Set the C++ standard and compiler flags
set(CMAKE_CXX_STANDARD 20)

# Define paths to SDL and SDL_mixer prebuilt libraries
set(SDL_DIR "${CMAKE_SOURCE_DIR}/sdk/sdl")
set(SDL_MIXER_DIR "${CMAKE_SOURCE_DIR}/sdk/sdl_mixer")

# Add SDL includes and libraries based on the build configuration
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(SDL_LIB "${SDL_DIR}/debug/SDL3.dll")
  set(SDL_LIB_IMPORT "${SDL_DIR}/debug/SDL3.lib")
  set(SDL_MIXER_LIB "${SDL_MIXER_DIR}/debug/SDL3_mixer.dll")
  set(SDL_MIXER_LIB_IMPORT "${SDL_MIXER_DIR}/debug/SDL3_mixer.lib")
else()
  set(SDL_LIB "${SDL_DIR}/release/SDL3.dll")
  set(SDL_LIB_IMPORT "${SDL_DIR}/release/SDL3.lib")
  set(SDL_MIXER_LIB "${SDL_MIXER_DIR}/release/SDL3_mixer.dll")
  set(SDL_MIXER_LIB_IMPORT "${SDL_MIXER_DIR}/release/SDL3_mixer.lib")
endif()

# Add include directories for SDL and SDL_mixer
include_directories("${SDL_DIR}/include")
include_directories("${SDL_MIXER_DIR}/include")

# Link against the prebuilt SDL and SDL_mixer libraries
add_library(SDL3 SHARED IMPORTED)
set_target_properties(SDL3 PROPERTIES
        IMPORTED_LOCATION "${SDL_LIB}"
        IMPORTED_IMPLIB "${SDL_LIB_IMPORT}"
)

add_library(SDL3_mixer SHARED IMPORTED)
set_target_properties(SDL3_mixer PROPERTIES
        IMPORTED_LOCATION "${SDL_MIXER_LIB}"
        IMPORTED_IMPLIB "${SDL_MIXER_LIB_IMPORT}"
)

# Add the main source directories
add_subdirectory(src)