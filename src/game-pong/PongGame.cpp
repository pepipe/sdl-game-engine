#include "PongGame.h"

#include "Ball.h"
#include "Paddle.h"
#include "Collision2D.h"

bool PongGame::Init(const char* title, const int width, const int height)
{
    if (!GameEngine::Init(title, width, height)) return false;

    // Create paddles and ball
    _player1 = std::make_shared<Paddle>(300.0f, height / 2.0f - 50, 10.0f, 100.0f, 350.0f, false, height);
    _player2 = std::make_shared<Paddle>(width - 310.0f, height / 2.0f - 50, 10.0f, 100.0f, 350.0f, true, height);
    _ball = std::make_shared<Ball>(width / 2.0f, height / 2.0f, 10.0f, 200.0f, 200.0f, width, height);
    
    _gameObjectManager.AddObject(_player1);
    _gameObjectManager.AddObject(_player2);
    _gameObjectManager.AddObject(_ball);

    return true;
}

void PongGame::Update()
{
    GameEngine::Update();

    // Check for collisions
    if (Collision2D::CheckCollision(_ball->GetRect(), _player1->GetRect())) {
        // Handle collision with player1
        HandleBallPaddleCollision();
    }
    if (Collision2D::CheckCollision(_ball->GetRect(), _player2->GetRect())) {
        // Handle collision with player2
        HandleBallPaddleCollision();
    }
}

// ReSharper disable once CppMemberFunctionMayBeConst
void PongGame::HandleBallPaddleCollision()
{
    _ball->FlipHorizontalMovement();
}
