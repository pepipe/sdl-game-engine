#include "PongGame.h"

bool PongGame::Init(const char* title, const int width, const int height)
{
    if (!GameEngine::Init(title, width, height)) return false;

    // Create paddles and ball
    // _gameObjectManager.AddObject(std::make_unique<Paddle>(50, height / 2 - 50, 10, 100, 300));
    // _gameObjectManager.AddObject(std::make_unique<Paddle>(width - 60, height / 2 - 50, 10, 100, 300));
    // _gameObjectManager.AddObject(std::make_unique<Ball>(width / 2, height / 2, 10, 200, 200));

    return true;
}
