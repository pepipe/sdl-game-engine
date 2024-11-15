#include "SpaceInvadersGame.h"
#include "SpaceInvadersConfig.h"

namespace SpaceInvaders
{
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
        CreateEnemies();

        return true;
    }

    void SpaceInvadersGame::Update()
    {
        GameEngine::Update();
    }

    void SpaceInvadersGame::RenderObjects()
    {
        // //Draw images
        // SDL_Texture* playerTexture = _imageManager.GetTexture("Player"); // Assume GetTexture loads or retrieves a texture
        // float playerWidth, playerHeight;
        // SDL_GetTextureSize(playerTexture, &playerWidth, &playerHeight);
        // const SDL_FRect playerDstRect = {0.f, 0.f, playerWidth, playerHeight};
        // SDL_RenderTexture(_renderer, playerTexture, nullptr, &playerDstRect);

        GameEngine::RenderObjects();
    }


    void SpaceInvadersGame::LoadAssets()
    {
        //Images
        _imageManager.LoadTexture("Player", "assets/images/player.png", _renderer);
        //SpriteSheets
        _spriteSheetManager.LoadSpriteSheet("Enemy1", "assets/images/enemy-1.png", 64, 64, _renderer);
        _spriteSheetManager.LoadSpriteSheet("Enemy2", "assets/images/enemy-2.png", 128, 64, _renderer);
        _spriteSheetManager.LoadSpriteSheet("Enemy3", "assets/images/enemy-3.png", 128, 64, _renderer);
        //Audio
        //Fonts
    }

    void SpaceInvadersGame::CreateEnemies()
    {
        for (int i = 0; i < 5; ++i)
        {
            auto enemySpriteName = GetEnemyName(i);
            auto enemyWidth = GetEnemyWidth(i);
            const auto horizontalSpacing = i == 0 ? SMALL_ENEMY_HORIZONTAL_SPACING : LARGE_ENEMY_HORIZONTAL_SPACING;
            float enemyHeight = 64.0f;
            for (int j = 0; j < 10; ++j)
            {
                auto enemyPos = Vector2D(0 + j * (enemyWidth + horizontalSpacing), 0 + i * (enemyHeight + ENEMY_VERTICAL_SPACING));
                
                auto enemy = std::make_shared<Enemy>(enemyWidth, enemyHeight, enemyPos, _spriteSheetManager,
                                                            enemySpriteName, 2, 2.0f);
                _gameObjectManager.AddObject(enemy);
                _enemyLines[i][j] = enemy;
            }
        }
    }

    std::string SpaceInvadersGame::GetEnemyName(const int line)
    {
        if(line == 0) return "Enemy1";
        if(line > 0 && line < 3) return "Enemy2";

        return "Enemy3";
    }

    float SpaceInvadersGame::GetEnemyWidth(const int line)
    {
        if(line == 0) return 64.0f;

        return 128.0f;
    }

}
