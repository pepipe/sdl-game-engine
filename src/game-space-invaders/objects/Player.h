#pragma once

#include <array>
#include "Bullet.h"
#include "EventQueue.h"
#include "GameObject2D.h"
#include "Image.h"

using GameEngine::Objects::GameObject2D;
using GameEngine::Images::Image;
using GameEngine::Utilities::Event;

namespace SpaceInvaders
{
    class Player final : public GameObject2D
    {
    public:
        Player(float width, float height, const Vector2D& playerPos, float speed, SDL_Texture* texture, int screenWidth);

        void HandleEvents(const SDL_Event& event) override;
        void Update(float deltaTime) override;
        void Render(SDL_Renderer* renderer) const override;
        std::array<std::shared_ptr<Bullet>, 10>& GetBullets();
    private:
        void OnGameOver(const Event& event);
        void FireBullet();
        std::shared_ptr<Bullet> GetNextAvailableBullet();

        SDL_Texture* _playerImage;
        float _speed;
        int _screenWidth;
        int _movement = 0;
        std::array<std::shared_ptr<Bullet>, 10> _bullets;
        bool _isLeftPressed = false;
        bool _isRightPressed = false;
        bool _isGameOver = false;
    };
}