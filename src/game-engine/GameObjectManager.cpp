#include "GameObjectManager.h"

void GameObjectManager::AddObject(std::shared_ptr<GameObject> obj)
{
    _gameObjects.push_back(std::move(obj));
}

void GameObjectManager::HandleEvents(const SDL_Event& event) const
{
    for (const auto& obj : _gameObjects)
    {
        obj->HandleEvents(event);
    }
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
