#pragma once

#include "GameObject2D.h"
#include "Image.h"

using GameEngine::Objects::GameObject2D;
using GameEngine::Images::Image;

class Player final : public GameObject2D
{
public:
    Player(float width, float height, const Vector2D& playerPos, SDL_Texture* texture);

    void HandleEvents(const SDL_Event& event) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) const override;
private:
    SDL_Texture* _playerImage;
};

