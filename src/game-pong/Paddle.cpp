#include "Paddle.h"

Paddle::Paddle(const float xPos, const float yPos, const float width, const float height, const float speed,
               const bool isRightPlayer, const int screenHeight) :
    GameObject2D(width, height, Vector2D(xPos, yPos)),
    _speed(speed),
    _isRightPlayer(isRightPlayer),
    _screenHeight(screenHeight)
{
}

void Paddle::HandleEvents(const SDL_Event& event)
{
    const auto keyUp = _isRightPlayer ? SDLK_UP : SDLK_W;
    const auto keyDown = _isRightPlayer ? SDLK_DOWN : SDLK_S;
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.key == keyUp)
        {
            _isUpPressed = true;
        }
        else if (event.key.key == keyDown)
        {
            _isDownPressed = true;
        }
    }
    else if (event.type == SDL_EVENT_KEY_UP)
    {
        if (event.key.key == keyUp)
        {
            _isUpPressed = false;
        }
        else if (event.key.key == keyDown)
        {
            _isDownPressed = false;
        }
    }

    // Determine movement based on key states
    if (_isUpPressed && !_isDownPressed)
    {
        _movement = -1; // Move up
    }
    else if (_isDownPressed && !_isUpPressed)
    {
        _movement = 1; // Move down
    }
    else 
    {
        _movement = 0; // Stop if both keys are pressed
    }
}

void Paddle::Update(const float deltaTime)
{
    _position.y += _movement * _speed * deltaTime;
    if(_position.y <= 0) _position.y = 0;
    else if (_position.y + _height >= _screenHeight) _position.y = _screenHeight - _height;
}

void Paddle::Render(SDL_Renderer* renderer) const
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    GameObject2D::Render(renderer);
}
