#include "PongGame.h"

#include <iostream>
#include <Random.h>

#include "Ball.h"
#include "Paddle.h"
#include "Collision2D.h"

bool PongGame::Init(const char* title, const int width, const int height)
{
    if (!GameEngine::Init(title, width, height)) return false;

    // Create paddles and ball
    _player1 = std::make_shared<Paddle>(300.0f, height / 2.0f - 50, 10.0f, 100.0f, 350.0f, false, height);
    _player2 = std::make_shared<Paddle>(width - 310.0f, height / 2.0f - 50, 10.0f, 100.0f, 350.0f, true, height);
    
    _gameObjectManager.AddObject(_player1);
    _gameObjectManager.AddObject(_player2);

    SpawnBall();

    return true;
}

void PongGame::Update()
{
    GameEngine::Update();

    if(!_ball || !_player1 || !_player2) return;
    
    // Check for collisions
    if (Collision2D::CheckCollision(_ball->GetRect(), _player1->GetRect())) {
        // Handle collision with player1
        HandleBallPaddleCollision();
    }
    if (Collision2D::CheckCollision(_ball->GetRect(), _player2->GetRect())) {
        // Handle collision with player2
        HandleBallPaddleCollision();
    }

    BallCheckHorizontalExit();
}

void PongGame::Render()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    DrawNet(_renderer);
    _gameObjectManager.Render(_renderer);

    SDL_RenderPresent(_renderer);
}

void PongGame::DrawNet(SDL_Renderer* renderer) const
{
    int screenWidth, screenHeight;
    SDL_GetCurrentRenderOutputSize(renderer, &screenWidth, &screenHeight);

    // Set color for the net (e.g., white)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Draw the net
    for (int y = 0; y < screenHeight; y += NET_HEIGHT + NET_SPACING) {
        SDL_FRect netRect = {
            screenWidth / 2.0f - NET_WIDTH / 2.0f,
            static_cast<float>(y),
            static_cast<float>(NET_WIDTH),
            static_cast<float>(NET_HEIGHT)
        };
        SDL_RenderFillRect(renderer, &netRect);
    }
}

void PongGame::SpawnBall()
{
    int xDirection = Random::GetRandomNumber(0, 1);
    xDirection = xDirection == 0 ? -1 : xDirection;
    float speedX = Random::GetRandomNumber(200.0f, 400.0f);
    speedX *= static_cast<float>(xDirection);

    float speedY = Random::GetRandomNumber(200.0f, 300.0f);
    
    _ball = std::make_shared<Ball>(_screenWidth / 2.0f, _screenHeight / 2.0f, 10.0f, speedX, speedY,
        _screenWidth, _screenHeight);
    _gameObjectManager.AddObject(_ball);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void PongGame::HandleBallPaddleCollision()
{
    _ball->FlipHorizontalMovement();
    auto ballSpeed = _ball->GetSpeed();
    ballSpeed.x += ballSpeed.x * 0.05f;
    _ball->SetSpeed(ballSpeed);
    std::cout << "Ball Speed: " << _scorePlayer1.GetScore() << std::endl;
}

void PongGame::BallCheckHorizontalExit()
{
    if(!_ball) return;

    if (_ball->GetPos().x + _ball->GetSize() > 0 && _ball->GetPos().x < _screenWidth)
        return;

    if (_ball->GetPos().x <= 0)
    {
        _scorePlayer2.IncreaseScore();
    }
    else if (_ball->GetPos().x >= _screenWidth)
    {
        _scorePlayer1.IncreaseScore();
    }

    std::cout << "Player 1 Score: " << _scorePlayer1.GetScore() << std::endl;
    std::cout << "Player 2 Score: " << _scorePlayer2.GetScore() << std::endl;
    SpawnBall();
}
