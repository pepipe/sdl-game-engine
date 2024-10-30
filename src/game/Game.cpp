#include <iostream>

#include "Game.h"

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr)
{
}

bool Game::Init(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    isRunning = true;
    return true;
}

void Game::Run()
{
    while (isRunning)
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
        if (event.type == SDL_EVENT_QUIT) isRunning = false;
    }
}

void Game::Update() {
    // Update game objects here
}

void Game::Render() const
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw objects here

    SDL_RenderPresent(renderer);
}

void Game::Clean() const
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Game::~Game() {
    Clean();
}