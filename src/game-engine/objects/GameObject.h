#pragma once

#include <SDL3/SDL_render.h>

class GameObject
{
public:
    GameObject(const float xPos, const float yPos, const float width, const float height) :
        _xPos(xPos), _yPos(yPos), _width(width), _height(height)
    {
    }

    SDL_FRect GetRect() const
    {
        return {_xPos, _yPos, _width, _height};
    }

    virtual void HandleEvents(const SDL_Event& event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(SDL_Renderer* renderer) const = 0;
    virtual ~GameObject() = default;

protected:
    float _xPos;
    float _yPos;
    float _width;
    float _height;
};
