# CMakeList.txt : CMake project for DeathRunSDL

cmake_minimum_required (VERSION 3.8)

project ("DeathRunSDL")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Add the SDL3 library
find_package(SDL3 REQUIRED)

# add source director
add_subdirectory(src)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET DeathRunSDL PROPERTY CXX_STANDARD 20)
endif()

# Set linker flags based on the compiler
if(MSVC)
    set(CMAKE_GENERATOR_TOOLSET "v143")
    set_target_properties(DeathRunSDL PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()