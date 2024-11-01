# Root CMakeLists.txt : CMake project for SDLEngine
cmake_minimum_required (VERSION 3.8)

project ("SDLEngine")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Set the C++ standard and compiler flags
set(CMAKE_CXX_STANDARD 20)

# Add SDL3 as a subdirectory instead of using find_package
add_subdirectory(external/SDL3)

# Add the main source directories
add_subdirectory(src)