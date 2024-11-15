#pragma once

#include <memory>
#include <vector>
#include "GameObject.h"

namespace GameEngine::Object
{
    class GameObjectManager
    {
    public:
        void AddObject(std::shared_ptr<GameObject> obj);
        void RemoveObject(const std::shared_ptr<GameObject>& obj);
        void HandleEvents(const SDL_Event& event) const;
        void Update(float deltaTime) const;
        void Render(SDL_Renderer* renderer) const;

    private:
        std::vector<std::shared_ptr<GameObject>> _gameObjects;
    };
}
