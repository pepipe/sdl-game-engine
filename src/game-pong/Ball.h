#pragma once

#include "GameObject2D.h"

class Ball final : public GameObject2D
{
public:
    Ball(float xPos, float yPos, float size, float speedX, float speedY, int screenWidth, int screenHeight);
    void FlipHorizontalMovement();
    float GetSize() const;
    Vector2D GetPos() const;
    Vector2D GetSpeed() const;
    void SetSpeed(const Vector2D& speed);

    void HandleEvents(const SDL_Event& event) override{/* No-op */};
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) const override;

private:
    Vector2D _speed;
    int _screenWidth;
    int _screenHeight;
};
