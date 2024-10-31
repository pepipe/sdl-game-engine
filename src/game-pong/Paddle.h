#pragma once

#include <SDL3/SDL_render.h>

#include "GameObject2D.h"

class Paddle final : public GameObject2D
{
public:
    Paddle(float xPos, float yPos, float width, float height, float speed, bool isRightPlayer, int screenHeight);

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
