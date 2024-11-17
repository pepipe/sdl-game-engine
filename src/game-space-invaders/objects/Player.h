#pragma once

#include "GameObject2D.h"
#include "Image.h"

using GameEngine::Objects::GameObject2D;
using GameEngine::Images::Image;

class Player final : public GameObject2D
{
public:
    Player(float width, float height, const Vector2D& playerPos, float speed, SDL_Texture* texture, int screenWidth);

    void HandleEvents(const SDL_Event& event) override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) const override;
private:
    SDL_Texture* _playerImage;
    float _speed;
    int _screenWidth;
    bool _isLeftPressed = false;
    bool _isRightPressed = false;
    int _movement;
};

