#pragma once

#include <SDL3/SDL_render.h>
#include "object/GameObject2D.h"

using GameEngine::Object::GameObject2D;
using GameEngine::Math::Vector2D;

namespace Pong
{
    class Paddle final : public GameObject2D
    {
    public:
        Paddle(float xPos, float yPos, float width, float height, float speed, bool isRightPlayer, int screenHeight);
        Vector2D GetPosition() const;

        void HandleEvents(const SDL_Event& event) override;
        void Update(float deltaTime) override;
        void Render(SDL_Renderer* renderer) const override;

    private:
        float _speed;
        bool _isRightPlayer;
        int _screenHeight;
        int _movement = 0;
        bool _isUpPressed = false;
        bool _isDownPressed = false;
    };
}
