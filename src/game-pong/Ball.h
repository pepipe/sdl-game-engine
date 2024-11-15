#pragma once

#include "GameObject2D.h"

class Ball final : public GameObject2D
{
public:
    Ball(float xPos, float yPos, float size, float speedX, float speedY, int screenWidth, int screenHeight);
    void FlipHorizontalMovement();
    float GetSize() const;
    Vector2D GetPosition() const;
    void SetPos(Vector2D newPos);
    Vector2D GetSpeed() const;
    void SetSpeed(const Vector2D& speed);

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) const override;

private:
    Vector2D _speed;
    int _screenWidth;
    int _screenHeight;
};
