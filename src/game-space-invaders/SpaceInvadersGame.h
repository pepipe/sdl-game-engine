#pragma once

#include "Enemy.h"
#include "GameEngine.h"

class SpaceInvadersGame : public GameEngine
{
public:
    bool Init(const char* title, int width, int height) override;
    void Update() override;
    void RenderObjects() override;

private:
    void LoadAssets();

    std::shared_ptr<Enemy> _enemy = nullptr;
};
