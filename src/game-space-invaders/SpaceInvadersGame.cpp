#include "SpaceInvadersGame.h"

bool SpaceInvadersGame::Init(const char* title, const int width, const int height)
{
    if (!GameEngine::Init(title, width, height)) return false;

    constexpr SDL_AudioDeviceID deviceId = 0; // Use default device ID
    SDL_AudioSpec desiredSpec;
    desiredSpec.freq = 44100; // Standard audio frequency
    desiredSpec.format = SDL_AUDIO_S16; // Standard audio format
    desiredSpec.channels = 2; // Stereo

    if (!InitAudio(deviceId, desiredSpec)) return false;
    if (!InitImage()) return false;
    if (!InitText()) return false;

    LoadAssets();

    _enemy = std::make_shared<Enemy>(64.0f, 64.0f, Vector2D(100.0f, 100.0f), _spriteSheetManager, "Enemy1", 2, 2.0f);
    _gameObjectManager.AddObject(_enemy);
    return true;
}

void SpaceInvadersGame::Update()
{
    GameEngine::Update();
}

void SpaceInvadersGame::RenderObjects()
{
    //Draw images
    SDL_Texture* playerTexture = _imageManager.GetTexture("Player"); // Assume GetTexture loads or retrieves a texture
    float playerWidth, playerHeight;
    SDL_GetTextureSize(playerTexture, &playerWidth, &playerHeight);
    const SDL_FRect playerDstRect = {0.f, 0.f, playerWidth, playerHeight};
    SDL_RenderTexture(_renderer, playerTexture, nullptr, &playerDstRect);

    GameEngine::RenderObjects();
}


void SpaceInvadersGame::LoadAssets()
{
    //Images
    _imageManager.LoadTexture("Player", "assets/images/player.png", _renderer);
    //SpriteSheets
    _spriteSheetManager.LoadSpriteSheet("Enemy1", "assets/images/enemy-1.png", 64, 64, _renderer);
    //Audio
    //Fonts
}
