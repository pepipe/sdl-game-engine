#include "Enemy.h"

#include <iostream>
#include "EventTypes.h"
#include "GameEngine.h"

namespace SpaceInvaders
{
    Enemy::Enemy(const float width, const float height, const Vector2D& enemyPos, const int screenWidth, const int screenHeight,
            SpriteSheet& spriteSheet, const std::string& spriteName, const int totalFrames, const float framesPerSecond) :
        GameObject2D(width, height, enemyPos),

        _spriteSheet(spriteSheet),
        _spriteAnimation(SpriteAnimation(spriteName, totalFrames, framesPerSecond)),
        _screenWidth(screenWidth),
        _screenHeight(screenHeight),
        _framesPerSecond(framesPerSecond)
    {
        GameEngine::GameEngine::RegisterListener(EVENT_MAKE_ENEMIES_CLOSER,
            [this](const Event& event) { this->OnMakeEnemiesCloser(event); });
        GameEngine::GameEngine::RegisterListener(EVENT_GAME_OVER,
            [this](const Event& event) { this->OnGameOver(event); });
    }

    void Enemy::Update(const float deltaTime)
    {
        _timeAccumulator += deltaTime;
        if (_timeAccumulator >= _moveWaitTime) {
            _position.x += _movement * 10.f;
            _timeAccumulator = 0.0f;
        }
        
        _spriteAnimation.Update(deltaTime);

        if(_position.x + _width >= _screenWidth)
        {
            auto event = Event(EVENT_ENEMY_REACH_HORIZONTAL_END);
            event.data["direction"] = 1;
            GameEngine::GameEngine::AddEvent(event);
        }else if(_position.x < 0)
        {
            auto event = Event(EVENT_ENEMY_REACH_HORIZONTAL_END);
            event.data["direction"] = -1;
            GameEngine::GameEngine::AddEvent(event);
        }

        if(_position.y >= _screenHeight - PLAYER_BOTTOM_MARGIN - PLAYER_HEIGHT)
        {
            GameEngine::GameEngine::AddEvent(Event(EVENT_ENEMY_REACH_VERTICAL_END));
        }
    }

    void Enemy::Render(SDL_Renderer* renderer) const
    {
        const auto imageName = _spriteAnimation.GetSpriteName();
        const auto texture = _spriteSheet.GetTexture(imageName);
        const SDL_FRect* srcRect = _spriteSheet.GetSpriteFRect(imageName, _spriteAnimation.GetCurrentFrame());
        const SDL_FRect dstRect = {_position.x, _position.y, srcRect->w, srcRect->h};
        SDL_SetTextureColorMod(texture, _spriteColor.r, _spriteColor.g, _spriteColor.b);
        SDL_RenderTexture(renderer, texture, srcRect, &dstRect);
    }

    void Enemy::SetColor(const SDL_Color color)
    {
        _spriteColor = color;
    }

    void Enemy::OnMakeEnemiesCloser(const Event& event)
    {
        _movement *= -1;
        _position.y += _height;
        _moveWaitTime -= ENEMY_MOVE_WAIT_TIME_REDUCTION;
        if(_moveWaitTime <= 0.075f)
        {
            _moveWaitTime = 0.075f;
            return;
        }
        _framesPerSecond += ENEMY_INCREASE_ANIMATION_FPS;
        _spriteAnimation.SetFramesPerSecond(_framesPerSecond);
    }

    void Enemy::OnGameOver(const Event& event)
    {
        _movement = 0;
        _spriteAnimation.SetFramesPerSecond(0);
    }

}
