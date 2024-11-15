#pragma once

#include <SDL3/SDL_render.h>

namespace GameEngine::Objects
{
    class GameObject
    {
    public:
        GameObject(const float width, const float height) :
            _width(width), _height(height)
        {
        }
        float GetWidth() const {return _width;}
        float GetHeight() const {return _height;}

        virtual void HandleEvents(const SDL_Event& event) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Render(SDL_Renderer* renderer) const = 0;
        virtual ~GameObject() = default;

    protected:
        float _width;
        float _height;
    };
}