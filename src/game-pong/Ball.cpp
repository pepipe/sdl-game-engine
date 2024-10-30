#include "Ball.h"

#include <physics/Collision2D.h>

Ball::Ball(const float xPos, const float yPos, const float size, const float speedX, const float speedY, const int screenWidth,
           const int screenHeight) :
    GameObject(xPos, yPos, size, size),
    _speedX(speedX),
    _speedY(speedY),
    _screenWidth(screenWidth),
    _screenHeight(screenHeight)
{
}

void Ball::Update(const float deltaTime)
{
    _xPos += _speedX * deltaTime;
    _yPos += _speedY * deltaTime;

    // Bounce off screen edges
    if (_yPos <= 0 || _yPos >= _screenHeight - GetSize()) _speedY = -_speedY;

    //Collision2D::CheckCollision()
}

void Ball::Render(SDL_Renderer* renderer) const
{
    const SDL_FRect rect = {_xPos, _yPos, GetSize(), GetSize()};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

float Ball::GetSize() const
{
    return _width;
}

