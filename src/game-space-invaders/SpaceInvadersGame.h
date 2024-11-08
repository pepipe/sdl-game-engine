#pragma once
#include "GameEngine.h"

class SpaceInvadersGame : public GameEngine
{
public:
    bool Init(const char* title, int width, int height) override;
    void Update() override;
    void Render() override;

private:
    void LoadAssets();
};