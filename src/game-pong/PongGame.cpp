#include "PongGame.h"

#include "Ball.h"
#include "Paddle.h"

bool PongGame::Init(const char* title, const int width, const int height)
{
    if (!GameEngine::Init(title, width, height)) return false;

    // Create paddles and ball
    std::unique_ptr<GameObject> player1 = std::make_unique<Paddle>(300, height / 2 - 50, 10, 100, 350, false, height);
    std::unique_ptr<GameObject> player2 = std::make_unique<Paddle>(width - 310, height / 2 - 50, 10, 100, 350, true, height);

    _gameObjectManager.AddObject(std::move(player1));
    _gameObjectManager.AddObject(std::move(player2));
    _gameObjectManager.AddObject(std::make_unique<Ball>(width / 2, height / 2, 10, 200, 200, width, height));

    return true;
}
