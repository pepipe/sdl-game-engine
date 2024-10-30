#include "Paddle.h"

Paddle::Paddle(const float xPos, const float yPos, const float width, const float height, const float speed,
               const bool isRightPlayer, const int screenHeight) :
    GameObject(xPos, yPos),
    _width(width),
    _height(height),
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
    _yPos += _movement * _speed * deltaTime;
    if(_yPos <= 0) _yPos = 0;
    else if (_yPos + _height >= _screenHeight) _yPos = _screenHeight - _height;
}

void Paddle::Render(SDL_Renderer* renderer) const
{
    const SDL_FRect rect = {_xPos, _yPos, _width, _height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}
