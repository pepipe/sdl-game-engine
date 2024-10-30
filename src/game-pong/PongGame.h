#pragma once

#include "GameEngine.h"
#include "Ball.h"
#include "Paddle.h"

class PongGame : public GameEngine
{
public:
    bool Init(const char* title, int width, int height) override;
    void Update() override;

private:
    void HandleBallPaddleCollision();

    std::shared_ptr<Paddle> _player1;
    std::shared_ptr<Paddle> _player2;
    std::shared_ptr<Ball> _ball;
};
