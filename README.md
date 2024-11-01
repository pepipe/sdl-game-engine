## SDL GameEngine
Little game engine based on SDL.

### Build project on Windows
#### Requirements
1. Visual Studio 2022 with C++ toolset (v143)
2. CMake
3. SDL3
	1. git clone https://github.com/libsdl-org/SDL.git
	2. cd SDL
	3. mkdir build and cd build
	4. cmake .. -DSDL_SHARED=ON -DSDL_STATIC=OFF
	5. cmake --build . --config Release
	6. cmake --build . --config Debug 
	7. cmake --install . --config Release (need admin) 
	8. cmake --install . --config Debug (need admin) 

check here: https://github.com/libsdl-org/SDL/blob/preview-3.1.3/docs/README-cmake.md
