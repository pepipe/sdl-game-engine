#pragma once
#include "Colors.h"
#include "GameObject2D.h"

using GameEngine::Objects::GameObject2D;

namespace SpaceInvaders
{
    class Bullet final : public GameObject2D
    {
    public:
        Bullet(float width, float height, const Vector2D& startPos);

        void Update(float deltaTime) override;
        void Render(SDL_Renderer* renderer) const override;
        void SetColor(SDL_Color color);
        void SetSpeed(float speed);
        void SetActive(bool isActive);
        bool IsActive() const;

    private:
        SDL_Color _color = GameEngine::Color::White;
        float _speed = 400.0f;
        bool _active = false;
    };
}
