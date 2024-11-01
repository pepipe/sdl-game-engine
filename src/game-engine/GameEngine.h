#pragma once
#include <SDL3/SDL.h>

#include "GameObjectManager.h"

class GameEngine {
public:
    explicit GameEngine(bool capFPS = false);
    ~GameEngine();
    virtual bool Init(const char* title, int width, int height);
    void Run();
    virtual void HandleEvents();
    virtual void Update();
    virtual void Render();
    void Clean() const;

protected:
    SDL_Renderer* _renderer = nullptr;
    GameObjectManager _gameObjectManager;
    int _screenWidth;
    int _screenHeight;

private:
    const int FPS = 60;
    const float FRAME_TARGET_TIME = 1000.0f / FPS;

    bool _capFPS;
    bool _isRunning = false;
    SDL_Window* _window = nullptr;
    Uint64 _lastFrameTime = 0;
};
