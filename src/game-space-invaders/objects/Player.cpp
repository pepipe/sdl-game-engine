#include "Player.h"

Player::Player(const float width, const float height, const Vector2D& playerPos, const float speed, SDL_Texture* texture, const int screenWidth) :
    GameObject2D(width, height, playerPos),
    _playerImage(texture),
    _speed(speed),
    _screenWidth(screenWidth)
{
}

void Player::HandleEvents(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.key == SDLK_LEFT || event.key.key == SDLK_A)
        {
            _isLeftPressed = true;
        }
        else if (event.key.key == SDLK_RIGHT || event.key.key == SDLK_D)
        {
            _isRightPressed = true;
        }
    }
    else if (event.type == SDL_EVENT_KEY_UP)
    {
        if (event.key.key == SDLK_LEFT || event.key.key == SDLK_A)
        {
            _isLeftPressed = false;
        }
        else if (event.key.key == SDLK_RIGHT || event.key.key == SDLK_D)
        {
            _isRightPressed = false;
        }
    }

    // Determine movement based on key states
    if (_isLeftPressed && !_isRightPressed)
    {
        _movement = -1; // Move Left
    }
    else if (_isRightPressed && !_isLeftPressed)
    {
        _movement = 1; // Move Right
    }
    else 
    {
        _movement = 0; // Stop if both keys are pressed
    }
}

void Player::Update(const float deltaTime)
{
    _position.x += _movement * _speed * deltaTime;
    if(_position.x <= 0) _position.x = 0;
    else if (_position.x + _width >= _screenWidth) _position.x = _screenWidth - _width;
}

void Player::Render(SDL_Renderer* renderer) const
{
    float playerWidth, playerHeight;
    SDL_GetTextureSize(_playerImage, &playerWidth, &playerHeight);
    const SDL_FRect playerDstRect = {_position.x, _position.y, playerWidth, playerHeight};
    SDL_RenderTexture(renderer, _playerImage, nullptr, &playerDstRect);
}

