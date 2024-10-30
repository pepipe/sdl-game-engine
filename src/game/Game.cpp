#include <iostream>

#include "Game.h"

Game::Game(const bool capFPS) :
_capFPS(capFPS),
ball ({ 20, 20, 15, 15 })
{
}

bool Game::Init(const char* title, const int width, const int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

void Game::Run()
{
    while (_isRunning)
    {
        HandleEvents();
        Update();
        Render();
    }
}

void Game::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT) _isRunning = false;
    }
}

void Game::Update() {
    if(_capFPS)
    {
        const auto time_to_wait = FRAME_TARGET_TIME - SDL_GetTicks() - _lastFrameTime;
        if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        {
            SDL_Delay(time_to_wait);
        }
    }

    // get a delta time factor converted to seconds to be used to update objects
    const auto deltaTime = (SDL_GetTicks() - _lastFrameTime) / 1000.0f;
    _lastFrameTime = SDL_GetTicks();
    
    // Update game objects here
}

void Game::Render() const
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    // Draw objects here

    SDL_RenderPresent(_renderer);
}

void Game::Clean() const
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

Game::~Game() {
    Clean();
}