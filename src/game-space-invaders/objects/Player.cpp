#include "Player.h"

#include "EventTypes.h"
#include "GameEngine.h"

namespace SpaceInvaders
{
    Player::Player(const float width, const float height, const Vector2D& playerPos, const float speed, SDL_Texture* texture, const int screenWidth) :
        GameObject2D(width, height, playerPos),
        _playerImage(texture),
        _speed(speed),
        _screenWidth(screenWidth)
    {
        GameEngine::GameEngine::RegisterListener(EVENT_GAME_OVER,
            [this](const Event& event) { this->OnGameOver(event); });

        for (auto& bullet : _bullets) {
            bullet = std::make_shared<Bullet>(5.0f, 15.0f, Vector2D(300, 800));
        }
    }

    void Player::HandleEvents(const SDL_Event& event)
    {
        if(_isGameOver) return;

        if (event.type == SDL_EVENT_KEY_DOWN)
        {
            if (event.key.key == SDLK_LEFT || event.key.key == SDLK_A)
            {
                _isLeftPressed = true;
            }
            else if (event.key.key == SDLK_RIGHT || event.key.key == SDLK_D)
            {
                _isRightPressed = true;
            }
            else if(event.key.key == SDLK_SPACE)
            {
                FireBullet();
            }
        }
        else if (event.type == SDL_EVENT_KEY_UP)
        {
            if (event.key.key == SDLK_LEFT || event.key.key == SDLK_A)
            {
                _isLeftPressed = false;
            }
            else if (event.key.key == SDLK_RIGHT || event.key.key == SDLK_D)
            {
                _isRightPressed = false;
            }
        }

        // Determine movement based on key states
        if (_isLeftPressed && !_isRightPressed)
        {
            _movement = -1; // Move Left
        }
        else if (_isRightPressed && !_isLeftPressed)
        {
            _movement = 1; // Move Right
        }
        else 
        {
            _movement = 0; // Stop if both keys are pressed
        }
    }

    void Player::Update(const float deltaTime)
    {
        _position.x += _movement * _speed * deltaTime;
        if(_position.x <= 0) _position.x = 0;
        else if (_position.x + _width >= _screenWidth) _position.x = _screenWidth - _width;
    }

    void Player::Render(SDL_Renderer* renderer) const
    {
        float playerWidth, playerHeight;
        SDL_GetTextureSize(_playerImage, &playerWidth, &playerHeight);
        const SDL_FRect playerDstRect = {_position.x, _position.y, playerWidth, playerHeight};
        SDL_RenderTexture(renderer, _playerImage, nullptr, &playerDstRect);
    }

    std::array<std::shared_ptr<Bullet>, 10>& Player::GetBullets()
    {
        return _bullets;
    }

    void Player::OnGameOver(const Event& event)
    {
        _movement = 0;
        _isGameOver = true;
    }

    void Player::FireBullet()
    {
        const auto bullet = GetNextAvailableBullet();
        if(bullet == nullptr) return;

        bullet->SetPosition(Vector2D(_position.x + _width / 2.0f, _position.y - _height));
        bullet->SetActive(true);
    }

    std::shared_ptr<Bullet> Player::GetNextAvailableBullet()
    {
        for(auto& bullet : _bullets)
        {
            if(!bullet->IsActive()) return bullet;
        }

        return nullptr;
    }

}