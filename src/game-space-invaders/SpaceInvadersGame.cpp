#include "SpaceInvadersGame.h"

#include "Collision2D.h"
#include "EventTypes.h"
#include "SpaceInvadersConfig.h"
#include "Player.h"
#include "Colors.h"

using GameEngine::Physics::Collision2D;

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
        StartGame();

        return true;
    }

    void SpaceInvadersGame::HandleCustomEvents(const SDL_Event& event)
    {
        if(!_isGameOver) return;

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.key == SDLK_RETURN ||
                event.key.key == SDLK_RETURN2 ||
                event.key.key == SDLK_KP_ENTER)
            {
                ResetGame();
                StartGame();
            }
        }
    }

    void SpaceInvadersGame::Update()
    {
        if(_isGameOver) return;
        
        GameEngine::Update();

        CheckCollisions();
    }

    void SpaceInvadersGame::RenderObjects()
    {
        GameEngine::RenderObjects();
        if(_isGameOver)
        {
            const SDL_FRect dstTextRect = {_screenWidth / 2.0f - 300, _screenHeight / 2.0f - 150, 600.0f, 300.0f};
            _textManager.RenderText(_renderer, _gameOverText, nullptr, &dstTextRect);
        }
    }

    void SpaceInvadersGame::StartGame()
    {
        CreateEnemies();
        _player = std::make_shared<Player>(PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(_screenWidth / 2.0f, _screenHeight - PLAYER_BOTTOM_MARGIN),
            PLAYER_SPEED, _imageManager.GetTexture("Player"), _screenWidth);
        _gameObjectManager.AddObject(_player);
        for(auto& bullet : _player->GetBullets())
        {
            _gameObjectManager.AddObject(bullet);
        }

        RegisterListener(EVENT_ENEMY_REACH_HORIZONTAL_END,
            [this](const Event& event) { this->OnHorizontalEnd(event); });
        RegisterListener(EVENT_ENEMY_REACH_VERTICAL_END,
                    [this](const Event& event) { this->OnVerticalEnd(event); });
    }

    void SpaceInvadersGame::ResetGame()
    {
        ClearEventQueue();
        // Nullify the bullets
        for (auto& bullet : _player->GetBullets())
        {
            bullet = nullptr;
        }
        _player = nullptr; 
        _gameObjectManager.ClearObjects();
        SDL_Delay(100);
        _isGameOver = false;
        _lastDirection = 0;
        SDL_Delay(100);
    }

    void SpaceInvadersGame::GameOver()
    {
        AddEvent(Event(EVENT_GAME_OVER));
        _gameOverText = _textManager.CreateTextSurface("DIGIT-LARGE", "GAME OVER", ::GameEngine::Color::White, _renderer);
        _isGameOver = true;
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
        _textManager.LoadFont("DIGIT-LARGE", "assets/fonts/DS-DIGIT.ttf", 100.0f);
    }

    void SpaceInvadersGame::CheckCollisions()
    {
        int enemiesAlive = 0;
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 10; ++j)
            {
                if(!_enemyLines[i][j]->IsActive()) continue;

                ++enemiesAlive;
                for(const auto& bullet : _player->GetBullets())
                {
                    if(!bullet->IsActive()) continue;

                    if(Collision2D::CheckCollision(bullet->GetRect(), _enemyLines[i][j]->GetRect()))
                    {
                        _gameObjectManager.RemoveObject(_enemyLines[i][j]);
                        _enemyLines[i][j]->SetActive(false);
                        bullet->SetActive(false);
                    }
                }
            }
        }

        if(enemiesAlive == 0) GameOver();
    }

    void SpaceInvadersGame::CreateEnemies()
    {
        for (int i = 0; i < 5; ++i)
        {
            auto enemySpriteName = GetEnemyName(i);
            auto enemyWidth = GetEnemyWidth(i);
            const auto enemyColor = GetEnemyColor(i);
            const auto horizontalSpacing = i == 0 ? SMALL_ENEMY_HORIZONTAL_SPACING : LARGE_ENEMY_HORIZONTAL_SPACING;
            const float leftMargin = i == 0 ? 20.0f : .0f;
            float enemyHeight = 64.0f;
            for (int j = 0; j < 10; ++j)
            {
                auto enemyPos = Vector2D(leftMargin + j * (enemyWidth + horizontalSpacing),
                                         enemyHeight + i * (enemyHeight + ENEMY_VERTICAL_SPACING));
                auto enemy = std::make_shared<Enemy>(enemyWidth, enemyHeight, enemyPos, _screenWidth, _screenHeight, 
                                                    _spriteSheetManager, enemySpriteName, 2, 2.0f);
                enemy->SetColor(enemyColor);
                _gameObjectManager.AddObject(enemy);
                _enemyLines[i][j] = enemy;
            }
        }
    }

    std::string SpaceInvadersGame::GetEnemyName(const int line)
    {
        if (line == 0) return "Enemy1";
        if (line > 0 && line < 3) return "Enemy2";

        return "Enemy3";
    }

    float SpaceInvadersGame::GetEnemyWidth(const int line)
    {
        if (line == 0) return 64.0f;

        return 128.0f;
    }

    SDL_Color SpaceInvadersGame::GetEnemyColor(const int line)
    {
        if (line == 0) return ::GameEngine::Color::Magenta;
        if (line > 0 && line < 3) return ::GameEngine::Color::Yellow;
        return ::GameEngine::Color::White;
    }

    void SpaceInvadersGame::OnHorizontalEnd(const Event& event)
    {
        auto it = event.data.find("direction");
        if (it != event.data.end() && std::holds_alternative<int>(it->second)) {
            const auto direction = std::get<int>(it->second);
            if(_lastDirection == direction) return;
        
            _lastDirection = direction;
            AddEvent(Event(EVENT_MAKE_ENEMIES_CLOSER));
        }
    }

    void SpaceInvadersGame::OnVerticalEnd(const Event& event)
    {
        if(_isGameOver) return;

        GameOver();
    }

}
