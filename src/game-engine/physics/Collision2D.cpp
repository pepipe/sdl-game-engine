#include "Collision2D.h"

namespace GameEngine::Physics
{
    bool Collision2D::CheckCollision(const SDL_FRect& a, const SDL_FRect& b)
    {
        //AABB (Axis-Aligned Bounding Box)
        return a.x < b.x + b.w &&
               a.x + a.w > b.x &&
               a.y < b.y + b.h &&
               a.y + a.h > b.y;
    }
}
