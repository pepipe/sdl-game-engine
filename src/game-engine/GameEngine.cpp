#include <iostream>

#include "GameEngine.h"

GameEngine::GameEngine(const bool capFPS) :
_capFPS(capFPS)
{
}

bool GameEngine::Init(const char* title, const int width, const int height)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    _window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!_window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, nullptr);
    if (!_renderer)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return false;
    }

    _isRunning = true;
    return true;
}

void GameEngine::Run()
{
    while (_isRunning)
    {
        HandleEvents();
        Update();
        Render();
    }
}

void GameEngine::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT) _isRunning = false;
    }
}

void GameEngine::Update() {
    if(_capFPS)
    {
        const auto time_to_wait = FRAME_TARGET_TIME - SDL_GetTicks() - _lastFrameTime;
        if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        {
            SDL_Delay(static_cast<Uint32>(time_to_wait));
        }
    }

    // get a delta time factor converted to seconds to be used to update objects
    const auto deltaTime = (SDL_GetTicks() - _lastFrameTime) / 1000.0f;
    _lastFrameTime = SDL_GetTicks();
    
    // Update game objects here
    _gameObjectManager.Update(deltaTime);
}

void GameEngine::Render() const
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    // Draw objects here
    _gameObjectManager.Render(_renderer);

    SDL_RenderPresent(_renderer);
}

void GameEngine::Clean() const
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

GameEngine::~GameEngine() {
    Clean();
}