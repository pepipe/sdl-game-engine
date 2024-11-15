#pragma once
#include <SDL3/SDL.h>

#include "Audio.h"
#include "EventQueue.h"
#include "Image.h"
#include "SpriteSheet.h"
#include "object/GameObjectManager.h"
#include "text/Text.h"

using GameEngine::Object::GameObjectManager;
using GameEngine::Utilities::Event;
using GameEngine::Utilities::EventQueue;
using GameEngine::Utilities::EventHandler;
using GameEngine::Image::SpriteSheet;

namespace GameEngine
{
    class GameEngine {
    public:
        explicit GameEngine(bool capFPS = false);
        ~GameEngine();

        virtual bool Init(const char* title, int width, int height);
        bool InitAudio(SDL_AudioDeviceID deviceId, const SDL_AudioSpec& desiredSpec);
        bool InitImage();
        bool InitSpriteSheet();
        bool InitText();
        void Run();

        //Game Global Events
        static void AddEvent(const Event& event);
        static void RegisterListener(const std::string& eventType, const EventHandler& handler);
        static void UnregisterListener(const std::string& eventType, const EventHandler& handler);

        virtual void HandleEvents();
        virtual void Update();
        virtual void RenderObjects();

    protected:
        virtual void Clean();

        SDL_Renderer* _renderer = nullptr;
        GameObjectManager _gameObjectManager;
        int _screenWidth;
        int _screenHeight;
        Audio::Audio _audioManager;
        Image::Image _imageManager;
        SpriteSheet _spriteSheetManager;
        Text::Text _textManager;

    private:
        void Render();

        const int FPS = 60;
        const float FRAME_TARGET_TIME = 1000.0f / FPS;

        bool _capFPS;
        bool _isRunning = false;
        SDL_Window* _window = nullptr;
        Uint64 _lastFrameTime = 0;
        bool _audioInit = false;
        bool _imageInit = false;
        bool _textInit = false;
        static EventQueue _gameEventQueue;
    };
}