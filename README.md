## SDL GameEngine
Little game engine based on SDL.

### SDL Library
I'll add the dynamic libs and the includes folder for cmake to build. 

If want to compile the SDL (e.g. to have it static or update binaries) here there's a helper guide. 
#### Windows
I'm using this SDL libs:
* [SDL](https://github.com/libsdl-org/SDL.git)
* [SDL_image](https://github.com/libsdl-org/SDL_image.git)
* [SDL_mixer](https://github.com/libsdl-org/SDL_mixer.git)
* [SDL_ttf](https://github.com/libsdl-org/SDL_ttf.git)

##### Requirements
1. [NASM](https://www.nasm.us)
2. [YASM](https://yasm.tortall.net)
   * This need to be added manually to windows PATH env variable
3. [doxygen](https://www.doxygen.nl/download.html)

##### Build
1. Do this for every folder (e.g. SDL/ SDL_image/ etc)
   1. `mkdir build`
   2. `cd build`
   3. `cmake .. -DSDL_SHARED=ON` (this is for dynamic lib build)
   4. `cmake --build . --config Debug` or `cmake --build . --config Release`
2. SDL_image will give errors in some CMakeLists (at least when using CMake 3.31.0-rc2)
   1. The errors are in some lines that have `MATCHES`, change it for `STREQUAL`

### Build project on Windows
#### Requirements
1. Visual Studio 2022 with C++ toolset (v143)
2. CMake
3. SDL3

check here: https://github.com/libsdl-org/SDL/blob/preview-3.1.3/docs/README-cmake.md
