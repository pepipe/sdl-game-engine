#pragma once

#include "GameEngine.h"

class PongGame : public GameEngine
{
public:
    bool Init(const char* title, int width, int height) override;
};
