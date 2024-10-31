#pragma once
#include <SDL3/SDL_rect.h>

class Collision2D
{
public:
    static bool CheckCollision(const SDL_FRect& a, const SDL_FRect& b);
};
