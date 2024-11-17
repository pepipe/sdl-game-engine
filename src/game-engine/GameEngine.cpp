#include <iostream>

#include "GameEngine.h"

namespace GameEngine
{
    EventQueue GameEngine::_gameEventQueue;

    GameEngine::GameEngine(const bool capFPS) :
        _capFPS(capFPS)
    {
    }

    GameEngine::~GameEngine()
    {
        Clean();
    }

    bool GameEngine::Init(const char* title, const int width, const int height)
    {
        if (!SDL_Init(SDL_INIT_VIDEO))
        {
            std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            return false;
        }

        _screenWidth = width;
        _screenHeight = height;
        _window = SDL_CreateWindow(title, width, height, SDL_WINDOW_INPUT_FOCUS);
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

    void GameEngine::AddEvent(const Event& event)
    {
        _gameEventQueue.AddEvent(event);
    }

    void GameEngine::RegisterListener(const std::string& eventType, const EventHandler& handler)
    {
        _gameEventQueue.RegisterListener(eventType, handler);
    }

    void GameEngine::UnregisterListener(const std::string& eventType, const EventHandler& handler)
    {
        _gameEventQueue.UnregisterListener(eventType, handler);
    }

    bool GameEngine::InitAudio(const SDL_AudioDeviceID deviceId, const SDL_AudioSpec& desiredSpec)
    {
        _audioInit = _audioManager.Init(deviceId, &desiredSpec);
        return _audioInit;
    }

    bool GameEngine::InitImage()
    {
        _imageInit = _imageManager.Init();
        return _imageInit;
    }

    bool GameEngine::InitSpriteSheet()
    {
        if(_imageInit) return _imageInit;
        _imageInit = _spriteSheetManager.Init();
        return _imageInit;
    }

    bool GameEngine::InitText()
    {
        _textInit = _textManager.Init();
        return _textInit;
    }

    void GameEngine::Update()
    {
        if (_capFPS)
        {
            if (const auto timeToWait =
                FRAME_TARGET_TIME - SDL_GetTicks() - _lastFrameTime; timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
            {
                SDL_Delay(static_cast<Uint32>(timeToWait));
            }
        }

        // get a delta time factor converted to seconds to be used to update objects
        const auto deltaTime = (SDL_GetTicks() - _lastFrameTime) / 1000.0f;
        _lastFrameTime = SDL_GetTicks();

        //Process event queue
        _gameEventQueue.ProcessEvents();

        // Update game objects here
        _gameObjectManager.Update(deltaTime);
    }

    void GameEngine::RenderObjects()
    {
        _gameObjectManager.Render(_renderer);
    }

    void GameEngine::Clean()
    {
        if(_audioInit) _audioManager.Clean();
        if(_imageInit) _imageManager.Clean();
        if(_imageInit) _spriteSheetManager.Clean();
        if(_textInit) _textManager.Clean();
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    void GameEngine::ClearEventQueue()
    {
        _gameEventQueue.ClearEventQueue();
    }


    void GameEngine::HandleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) _isRunning = false;

            HandleCustomEvents(event);
            //handle events in game objects
            _gameObjectManager.HandleEvents(event);
        }
    }

    void GameEngine::Render()
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);

        // Draw objects here
        RenderObjects();

        SDL_RenderPresent(_renderer);
    }
}