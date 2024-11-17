#pragma once

#include "Colors.h"
#include "EventQueue.h"
#include "SpriteAnimation.h"
#include "SpriteSheet.h"
#include "GameObject2D.h"
#include "SpaceInvadersConfig.h"

using GameEngine::Objects::GameObject2D;
using GameEngine::Math::Vector2D;
using GameEngine::Images::SpriteSheet;
using GameEngine::Images::SpriteAnimation;
using GameEngine::Utilities::Event;

namespace SpaceInvaders
{
    class Enemy final : public GameObject2D
    {
    public:
        Enemy(float width, float height, const Vector2D& enemyPos, int screenWidth, int screenHeight,
            SpriteSheet& spriteSheet, const std::string& spriteName, int totalFrames, float framesPerSecond);
        ~Enemy() override
        {
            std::cout << "Destroying Enemy" << std::endl;
        }

        void SetColor(SDL_Color color);
        void Update(float deltaTime) override;
        void Render(SDL_Renderer* renderer) const override;

    private:
        void OnMakeEnemiesCloser(const Event& event);
        void OnGameOver(const Event& event);

        SpriteSheet& _spriteSheet;
        SpriteAnimation _spriteAnimation;
        int _screenWidth;
        int _screenHeight;
        float _framesPerSecond;
        SDL_Color _spriteColor = GameEngine::Color::White;
        float _timeAccumulator = 0.0f;
        int _movement = 1;
        float _moveWaitTime = ENEMY_MOVE_WAIT_TIME;
    };
}