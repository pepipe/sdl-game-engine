#include "Enemy.h"

#include "Colors.h"
#include "SpaceInvadersConfig.h"

namespace SpaceInvaders
{
    Enemy::Enemy(const float width, const float height, const Vector2D& enemyPos, SpriteSheet& spriteSheet,
                 const std::string& spriteName, const int totalFrames, const float framesPerSecond) :
        GameObject2D(width, height, enemyPos),

        _spriteSheet(spriteSheet),
        _spriteAnimation(SpriteAnimation(spriteName, totalFrames, framesPerSecond))
    {
    }

    void Enemy::Update(const float deltaTime)
    {
        _timeAccumulator += deltaTime;
        if (_timeAccumulator >= ENEMY_INITIAL_SPEED) {
            _position.x += 10.f;
            _timeAccumulator = 0.0f;
        }
        
        _spriteAnimation.Update(deltaTime);
    }

    void Enemy::Render(SDL_Renderer* renderer) const
    {
        const auto imageName = _spriteAnimation.GetSpriteName();
        const auto texture = _spriteSheet.GetTexture(imageName);
        const SDL_FRect* srcRect = _spriteSheet.GetSpriteFRect(imageName, _spriteAnimation.GetCurrentFrame());
        const SDL_FRect dstRect = {_position.x, _position.y, srcRect->w, srcRect->h};
        SDL_SetTextureColorMod(texture,
                               GameEngine::Utilities::Colors::Blue.r,
                               GameEngine::Utilities::Colors::Blue.g,
                               GameEngine::Utilities::Colors::Blue.b);
        SDL_RenderTexture(renderer, texture, srcRect, &dstRect);
    }
}
