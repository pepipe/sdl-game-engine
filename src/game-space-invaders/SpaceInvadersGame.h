#pragma once

#include "GameEngine.h"
#include "SpriteAnimation.h"

class SpaceInvadersGame : public GameEngine
{
public:
    bool Init(const char* title, int width, int height) override;
    void Update() override;
    void RenderObjects() override;

private:
    void LoadAssets();

    std::shared_ptr<SpriteAnimation> _enemy = nullptr;
};
