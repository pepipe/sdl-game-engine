#include "Collision2D.h"

bool Collision2D::CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    //AABB (Axis-Aligned Bounding Box)
    return a.x < b.x + b.w &&
           a.x + a.w > b.x &&
           a.y < b.y + b.h &&
           a.y + a.h > b.y;
}
