#include "Player.h"

Player::Player(const float width, const float height, const Vector2D& playerPos, SDL_Texture* texture) :
    GameObject2D(width, height, playerPos),
    _playerImage(texture)
{
}

void Player::HandleEvents(const SDL_Event& event)
{
    
}

void Player::Update(const float deltaTime)
{
    
}

void Player::Render(SDL_Renderer* renderer) const
{
    float playerWidth, playerHeight;
    SDL_GetTextureSize(_playerImage, &playerWidth, &playerHeight);
    const SDL_FRect playerDstRect = {_position.x, _position.y, playerWidth, playerHeight};
    SDL_RenderTexture(renderer, _playerImage, nullptr, &playerDstRect);
}

