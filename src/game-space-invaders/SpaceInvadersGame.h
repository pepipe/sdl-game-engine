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

        std::shared_ptr<Enemy> _enemy = nullptr;
    };
}