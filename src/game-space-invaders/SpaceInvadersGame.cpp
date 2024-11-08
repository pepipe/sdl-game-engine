#include "SpaceInvadersGame.h"

bool SpaceInvadersGame::Init(const char* title, const int width, const int height)
{
    if (!GameEngine::Init(title, width, height)) return false;
    
    constexpr SDL_AudioDeviceID deviceId = 0; // Use default device ID
    SDL_AudioSpec desiredSpec;
    desiredSpec.freq = 44100;       // Standard audio frequency
    desiredSpec.format = SDL_AUDIO_S16; // Standard audio format
    desiredSpec.channels = 2;       // Stereo

    if(!InitAudio(deviceId, desiredSpec)) return false;
    if(!InitImage()) return false;
    if(!InitText()) return false;

    LoadAssets();
    return true;
}

void SpaceInvadersGame::Update()
{
    GameEngine::Update();
}

void SpaceInvadersGame::RenderObjects()
{
    //Draw image
    SDL_Texture* texture = _image.GetTexture("Player"); // Assume GetTexture loads or retrieves a texture
    float width, height;
    SDL_GetTextureSize (texture, &width, &height);
    const SDL_FRect dstRect = { 50, 50, width, height };
    SDL_RenderTexture(_renderer, texture, nullptr, &dstRect);

    GameEngine::RenderObjects();
}


void SpaceInvadersGame::LoadAssets()
{
    //Images
    _image.LoadTexture("Player", "assets/images/player.png", _renderer);
    //Audio
    //Fonts
}