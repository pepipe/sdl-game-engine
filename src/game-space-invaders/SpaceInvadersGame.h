#pragma once

#include "Enemy.h"
#include "GameEngine.h"

namespace SpaceInvaders
{
    class SpaceInvadersGame final : public GameEngine::GameEngine
    {
    public:
        bool Init(const char* title, int width, int height) override;

    private:
        void HandleCustomEvents(const SDL_Event& event) override;
        void Update() override;
        void RenderObjects() override;

        void StartGame();
        void ResetGame();
        void LoadAssets();
        void CreateEnemies();
        static std::string GetEnemyName(int line);
        static float GetEnemyWidth(int line);
        static SDL_Color GetEnemyColor(int line);
        void OnHorizontalEnd(const Event& event);
        void OnVerticalEnd(const Event& event);

        std::shared_ptr<Enemy> _enemyLines[5][12];
        int _lastDirection = 0;
        bool _isGameOver = false;
        SDL_Texture* _gameOverText = nullptr;
    };
}