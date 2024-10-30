#pragma once

#include <GameObject.h>

class Ball final : public GameObject
{
public:
    Ball(float xPos, float yPos, float size, float speedX, float speedY, int screenWidth, int screenHeight);

    void HandleEvents(const SDL_Event& event) override{/* No-op */};
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) const override;

private:
    float _size;
    float _speedX;
    float _speedY;
    int _screenWidth;
    int _screenHeight;
};