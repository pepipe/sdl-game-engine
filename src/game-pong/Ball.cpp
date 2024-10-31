#include "Ball.h"

#include <physics/Collision2D.h>

Ball::Ball(const float xPos, const float yPos, const float size, const float speedX, const float speedY, const int screenWidth,
           const int screenHeight) :
    GameObject2D(size, size, Vector2D(xPos, yPos)),
    _speed(speedX, speedY),
    _screenWidth(screenWidth),
    _screenHeight(screenHeight)
{
}

void Ball::FlipHorizontalMovement()
{
    _speed.x = -_speed.x;
}

float Ball::GetSize() const
{
    return _width;
}

Vector2D Ball::GetPos() const
{
    return _position;
}

Vector2D Ball::GetSpeed() const
{
    return _speed;
}

void Ball::SetSpeed(const Vector2D& speed)
{
    _speed = speed;
}


void Ball::Update(const float deltaTime)
{
    _position.x += _speed.x * deltaTime;
    _position.y += _speed.y * deltaTime;

    // Bounce off screen edges
    if (_position.y < 0)
    {
        _speed.y = -_speed.y;
        _position.y = 0;
    }else if(_position.y > _screenHeight - GetSize())
    {
        _speed.y = -_speed.y;
        _position.y = _screenHeight - GetSize();
    }
}

void Ball::Render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    GameObject2D::Render(renderer);
}
