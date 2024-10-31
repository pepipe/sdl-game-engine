#pragma once

#include "GameObject.h"
#include "vector.h"

class GameObject3D : public GameObject
{
public:
    GameObject3D(const float width, const float height, const Vector3D& position) :
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
    }

protected:
    Vector3D _position;
};
