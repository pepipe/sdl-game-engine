#pragma once

#include <SDL3/SDL_rect.h>

namespace GameEngine::Physics
{
    class Collision2D
    {
    public:
        static bool CheckCollision(const SDL_FRect& a, const SDL_FRect& b);
    };
}
