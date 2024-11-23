# Root CMakeLists.txt : CMake project for SDLEngine
cmake_minimum_required(VERSION 3.8)

include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)

project("SDLEngine")

# Set the C++ standard and compiler flags
set(CMAKE_CXX_STANDARD 20)

# Define paths to SDL prebuilt libraries
set(SDL_DIR "${CMAKE_SOURCE_DIR}/libs/sdl")
set(SDL_IMAGE_DIR "${CMAKE_SOURCE_DIR}/libs/sdl_image")
set(SDL_MIXER_DIR "${CMAKE_SOURCE_DIR}/libs/sdl_mixer")
set(SDL_TTF_DIR "${CMAKE_SOURCE_DIR}/libs/sdl_ttf")

# Add SDL includes and libraries based on the build configuration
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(SDL_LIB "${SDL_DIR}/debug/SDL3.dll")
  set(SDL_LIB_IMPORT "${SDL_DIR}/debug/SDL3.lib")
  set(SDL_IMAGE_LIB "${SDL_IMAGE_DIR}/debug/SDL3_image.dll")
  set(SDL_IMAGE_LIB_IMPORT "${SDL_IMAGE_DIR}/debug/SDL3_image.lib")
  set(SDL_MIXER_LIB "${SDL_MIXER_DIR}/debug/SDL3_mixer.dll")
  set(SDL_MIXER_LIB_IMPORT "${SDL_MIXER_DIR}/debug/SDL3_mixer.lib")
  set(SDL_TTF_LIB "${SDL_TTF_DIR}/debug/SDL3_ttf.dll")
  set(SDL_TTF_LIB_IMPORT "${SDL_TTF_DIR}/debug/SDL3_ttf.lib")
else()
  set(SDL_LIB "${SDL_DIR}/release/SDL3.dll")
  set(SDL_LIB_IMPORT "${SDL_DIR}/release/SDL3.lib")
  set(SDL_IMAGE_LIB "${SDL_IMAGE_DIR}/release/SDL3_image.dll")
  set(SDL_IMAGE_LIB_IMPORT "${SDL_IMAGE_DIR}/release/SDL3_image.lib")
  set(SDL_MIXER_LIB "${SDL_MIXER_DIR}/release/SDL3_mixer.dll")
  set(SDL_MIXER_LIB_IMPORT "${SDL_MIXER_DIR}/release/SDL3_mixer.lib")
  set(SDL_TTF_LIB "${SDL_TTF_DIR}/release/SDL3_ttf.dll")
  set(SDL_TTF_LIB_IMPORT "${SDL_TTF_DIR}/release/SDL3_ttf.lib")
endif()

# Add include directories for SDL
include_directories("${SDL_DIR}/include")
include_directories("${SDL_IMAGE_DIR}/include")
include_directories("${SDL_MIXER_DIR}/include")
include_directories("${SDL_TTF_DIR}/include")

# Link against the prebuilt SDL libraries
add_library(SDL3 SHARED IMPORTED)
set_target_properties(SDL3 PROPERTIES
        IMPORTED_LOCATION "${SDL_LIB}"
        IMPORTED_IMPLIB "${SDL_LIB_IMPORT}"
)

add_library(SDL3_image SHARED IMPORTED)
set_target_properties(SDL3_image PROPERTIES
        IMPORTED_LOCATION "${SDL_IMAGE_LIB}"
        IMPORTED_IMPLIB "${SDL_IMAGE_LIB_IMPORT}"
)

add_library(SDL3_mixer SHARED IMPORTED)
set_target_properties(SDL3_mixer PROPERTIES
        IMPORTED_LOCATION "${SDL_MIXER_LIB}"
        IMPORTED_IMPLIB "${SDL_MIXER_LIB_IMPORT}"
)

add_library(SDL3_ttf SHARED IMPORTED)
set_target_properties(SDL3_ttf PROPERTIES
        IMPORTED_LOCATION "${SDL_TTF_LIB}"
        IMPORTED_IMPLIB "${SDL_TTF_LIB_IMPORT}"
)

# Add the main source directories
add_subdirectory(src)