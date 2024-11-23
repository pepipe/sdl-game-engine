#pragma once

#include "GameObject.h"
#include "vector.h"


using GameEngine::Math::Vector2D;

namespace GameEngine::Objects
{
    class GameObject2D : public GameObject
    {
    public:
        GameObject2D(const float width, const float height, const Vector2D& position) :
            GameObject(width, height),
            _position(position)
        {
        }

        void HandleEvents(const SDL_Event& event) override
        {
        }

        void Update(float deltaTime) override
        {
        }

        void Render(SDL_Renderer* renderer) const override
        {
            const SDL_FRect rect = GetRect();
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_FRect GetRect() const
        {
            return {_position.x, _position.y, _width, _height};
        }

        Vector2D GetPosition() const
        {
            return _position;
        }

        void SetPosition(const Vector2D& position)
        {
            _position = position;
        }

    protected:
        Vector2D _position;
    };
}