#include "PongGame.h"

#include "Ball.h"
#include "Paddle.h"

bool PongGame::Init(const char* title, const int width, const int height)
{
    if (!GameEngine::Init(title, width, height)) return false;

    // Create paddles and ball
    std::unique_ptr<GameObject> player1 = std::make_unique<Paddle>(300.0f, height / 2.0f - 50, 10.0f, 100.0f, 350.0f, false, height);
    std::unique_ptr<GameObject> player2 = std::make_unique<Paddle>(width - 310.0f, height / 2.0f - 50, 10.0f, 100.0f, 350.0f, true, height);
    
    _gameObjectManager.AddObject(std::move(player1));
    _gameObjectManager.AddObject(std::move(player2));
    _gameObjectManager.AddObject(std::make_unique<Ball>(width / 2.0f, height / 2.0f, 10.0f, 200.0f, 200.0f, width, height));

    return true;
}
