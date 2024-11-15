#include "Enemy.h"

Enemy::Enemy(const float width, const float height, const Vector2D& enemyPos, SpriteSheet& spriteSheet,
             const std::string& spriteName, const int totalFrames, const float framesPerSecond) :
    GameObject2D(width, height, enemyPos),

    _spriteSheet(spriteSheet),
    _spriteAnimation(SpriteAnimation(spriteName, totalFrames, framesPerSecond))
{
}

void Enemy::Update(const float deltaTime)
{
    _spriteAnimation.Update(deltaTime);
}

void Enemy::Render(SDL_Renderer* renderer) const
{
    const auto imageName = _spriteAnimation.GetSpriteName();
    const SDL_FRect* srcRect = _spriteSheet.GetSpriteFRect(imageName, _spriteAnimation.GetCurrentFrame());
    const SDL_FRect dstRect = {100, 100, srcRect->w, srcRect->h};
    SDL_RenderTexture(renderer, _spriteSheet.GetTexture(imageName), srcRect, &dstRect);
}
