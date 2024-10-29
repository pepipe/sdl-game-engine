#pragma once
#include <SDL3/SDL.h>

class Game {
public:
    Game();
    ~Game();
    bool Init(const char* title, int width, int height);
    void Run();
    void Update();
    void Render();
    void HandleEvents();
    void Clean() const;

private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
};