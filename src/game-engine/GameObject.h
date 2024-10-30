#pragma once

#include <SDL3/SDL_render.h>

class GameObject
{
public:
    virtual void HandleEvents(const SDL_Event& event) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(SDL_Renderer* renderer) const = 0;
    virtual ~GameObject() = default;
};
