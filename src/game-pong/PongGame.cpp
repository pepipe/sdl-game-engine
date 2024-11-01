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
    // Calculate positions based on screen dimensions
    _player1 = std::make_shared<Paddle>(width * 0.05f, height / 2.0f - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, false, height);
    _player2 = std::make_shared<Paddle>(width * 0.95f - PADDLE_WIDTH, height / 2.0f - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, true, height);
    
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
        std::cout << "Collision2D::CheckCollision Player1" << std::endl;
        const auto newPos = Vector2D(_player1->GetPosition().x + _player1->GetWidth(), _ball->GetPosition().y);
        HandleBallPaddleCollision(newPos);
    }
    if (Collision2D::CheckCollision(_ball->GetRect(), _player2->GetRect())) {
        // Handle collision with player2
        std::cout << "Collision2D::CheckCollision Player2" << std::endl;
        const auto newPos = Vector2D(_player2->GetPosition().x - _ball->GetWidth(), _ball->GetPosition().y);
        HandleBallPaddleCollision(newPos);
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
    if(_ball) _gameObjectManager.RemoveObject(_ball);

    int xDirection = Random::GetRandomNumber(0, 1);
    xDirection = xDirection == 0 ? -1 : xDirection;
    float speedX = Random::GetRandomNumber(BALL_MIN_SPEED_X, BALL_MAX_SPEED_X);
    speedX *= static_cast<float>(xDirection);

    float speedY = Random::GetRandomNumber(BALL_MIN_SPEED_Y, BALL_MAX_SPEED_Y);
    
    _ball = std::make_shared<Ball>(_screenWidth / 2.0f, _screenHeight / 2.0f, BALL_SIZE, speedX, speedY,
        _screenWidth, _screenHeight);
    _gameObjectManager.AddObject(_ball);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void PongGame::HandleBallPaddleCollision(const Vector2D& newPos)
{
    _ball->FlipHorizontalMovement();
    auto ballSpeed = _ball->GetSpeed();
    ballSpeed.x += ballSpeed.x * 0.05f;
    _ball->SetSpeed(ballSpeed);
    _ball->SetPos(newPos);
    std::cout << "Ball Speed: " << _scorePlayer1.GetScore() << std::endl;
}

void PongGame::BallCheckHorizontalExit()
{
    if(!_ball) return;

    if (_ball->GetPosition().x + _ball->GetSize() > 0 && _ball->GetPosition().x < _screenWidth)
        return;

    if (_ball->GetPosition().x <= 0)
    {
        _scorePlayer2.IncreaseScore();
    }
    else if (_ball->GetPosition().x >= _screenWidth)
    {
        _scorePlayer1.IncreaseScore();
    }

    std::cout << "Player 1 Score: " << _scorePlayer1.GetScore() << std::endl;
    std::cout << "Player 2 Score: " << _scorePlayer2.GetScore() << std::endl;
    SpawnBall();
}
