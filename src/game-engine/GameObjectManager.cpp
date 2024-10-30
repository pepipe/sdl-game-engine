#include "GameObjectManager.h"

void GameObjectManager::AddObject(std::unique_ptr<GameObject> obj)
{
    _gameObjects.push_back(std::move(obj));
}

void GameObjectManager::Update(const float deltaTime) const
{
    for (const auto& obj : _gameObjects)
    {
        obj->Update(deltaTime);
    }
}

void GameObjectManager::Render(SDL_Renderer* renderer) const
{
    for (const auto& obj : _gameObjects)
    {
        obj->Render(renderer);
    }
}
