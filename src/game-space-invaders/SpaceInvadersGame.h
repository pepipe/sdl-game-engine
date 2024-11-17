#pragma once

#include "Enemy.h"
#include "GameEngine.h"

namespace SpaceInvaders
{
    class SpaceInvadersGame : public GameEngine::GameEngine
    {
    public:
        bool Init(const char* title, int width, int height) override;
        void Update() override;
        void RenderObjects() override;

    private:
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
    };
}