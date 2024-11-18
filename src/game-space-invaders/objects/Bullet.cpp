#include "Bullet.h"

namespace SpaceInvaders
{
    Bullet::Bullet(const float width, const float height, const Vector2D& startPos) :
        GameObject2D(width, height, startPos)
    {
    }

    void Bullet::Update(const float deltaTime)
    {
        if(!_active) return;

        _position.y -= _speed * deltaTime;

        if(_position.y + _height < 0) _active = false; 
    }

    void Bullet::Render(SDL_Renderer* renderer) const
    {
        if(!_active) return;

        SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
        GameObject2D::Render(renderer);
    }

    void Bullet::SetColor(const SDL_Color color)
    {
        _color = color;
    }

    void Bullet::SetSpeed(const float speed)
    {
        _speed = speed;
    }

    void Bullet::SetActive(const bool isActive)
    {
        _active = isActive;
    }

    bool Bullet::IsActive() const
    {
        return _active;
    }
}