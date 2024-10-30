#pragma once

#include "GameEngine.h"
#include "Ball.h"
#include "Paddle.h"

class PongGame final : public GameEngine
{
public:
    bool Init(const char* title, int width, int height) override;
    void Update() override;
    void Render() override;

private:
    static void DrawNet(SDL_Renderer* renderer);
    void HandleBallPaddleCollision();

    std::shared_ptr<Paddle> _player1;
    std::shared_ptr<Paddle> _player2;
    std::shared_ptr<Ball> _ball;
};
