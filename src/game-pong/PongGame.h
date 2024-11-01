#pragma once

#include "GameEngine.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"


class PongGame final : public GameEngine
{
public:
    bool Init(const char* title, int width, int height) override;
    void Update() override;
    void Render() override;

private:
    void DrawNet(SDL_Renderer* renderer) const;
    void SpawnBall();
    void HandleBallPaddleCollision(const Vector2D& newPos);
    void BallCheckHorizontalExit();

    // Game Configuration
    // Paddle Configuration
    const float PADDLE_WIDTH = 10.0f;
    const float PADDLE_HEIGHT = 100.0f;
    const float PADDLE_SPEED = 350.0f;
    //Ball Configuration
    const float BALL_MIN_SPEED_X = 250.0f;
    const float BALL_MAX_SPEED_X = 450.0f;
    const float BALL_MIN_SPEED_Y = 150.0f;
    const float BALL_MAX_SPEED_Y = 300.0f;
    const float BALL_SIZE = 10.0f;
    // Net configuration
    const int NET_WIDTH = 7; // Width of each rectangle in the net
    const int NET_HEIGHT = 30; // Height of each rectangle in the net
    const int NET_SPACING = 20; // Space between each rectangle in the net

    std::shared_ptr<Paddle> _player1;
    std::shared_ptr<Paddle> _player2;
    std::shared_ptr<Ball> _ball;
    Score _scorePlayer1;
    Score _scorePlayer2;
};
