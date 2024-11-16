#pragma once

#include "Colors.h"
#include "SpriteAnimation.h"
#include "SpriteSheet.h"
#include "GameObject2D.h"

using GameEngine::Objects::GameObject2D;
using GameEngine::Math::Vector2D;
using GameEngine::Images::SpriteSheet;
using GameEngine::Images::SpriteAnimation;

namespace SpaceInvaders
{
    class Enemy final : public GameObject2D
    {
    public:
        Enemy(float width, float height, const Vector2D& enemyPos, SpriteSheet& spriteSheet,
              const std::string& spriteName, int totalFrames, float framesPerSecond);

        void SetColor(SDL_Color color);
        void Update(float deltaTime) override;
        void Render(SDL_Renderer* renderer) const override;

    private:
        SpriteSheet& _spriteSheet;
        SpriteAnimation _spriteAnimation;
        SDL_Color _spriteColor = GameEngine::Utilities::Colors::White;
        float _timeAccumulator = 0.0f;
    };
}