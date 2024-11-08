#include "SpaceInvadersGame.h"

bool SpaceInvadersGame::Init(const char* title, const int width, const int height)
{
    if (!GameEngine::Init(title, width, height)) return false;

    return true;
}
