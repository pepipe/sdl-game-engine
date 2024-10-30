#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"

class GameObjectManager
{
public:
    void AddObject(std::shared_ptr<GameObject> obj);
    void HandleEvents(const SDL_Event& event) const;
    void Update(float deltaTime) const;
    void Render(SDL_Renderer* renderer) const;

private:
    std::vector<std::shared_ptr<GameObject>> _gameObjects;
};
