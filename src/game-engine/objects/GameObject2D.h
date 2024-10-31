#pragma once

#include "GameObject.h"
#include "vector.h"

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
        SDL_FRect rect = GetRect();
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_FRect GetRect() const
    {
        return {_position.x, _position.y, _width, _height};
    }

protected:
    Vector2D _position;
};
