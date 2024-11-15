#include "PongGame.h"

#include <iostream>
#include "Random.h"
#include "Ball.h"
#include "Paddle.h"
#include "Collision2D.h"
#include "EventTypes.h"

using GameEngine::Physics::Collision2D;
using GameEngine::Utilities::Random;

namespace Pong
{
    PongGame::PongGame() :
        _scoreTextWidthPlayer1(0.0f),
        _scoreTextHeightPlayer1(0.0f),
        _scoreTextWidthPlayer2(0.0f),
        _scoreTextHeightPlayer2(0.0f)
    {
    }


    bool PongGame::Init(const char* title, const int width, const int height)
    {
        if (!GameEngine::Init(title, width, height)) return false;

        constexpr SDL_AudioDeviceID deviceId = 0; // Use default device ID
        SDL_AudioSpec desiredSpec;
        desiredSpec.freq = 44100;       // Standard audio frequency
        desiredSpec.format = SDL_AUDIO_S16; // Standard audio format
        desiredSpec.channels = 2;       // Stereo

        if(!InitAudio(deviceId, desiredSpec)) return false;
        if(!InitText()) return false;

        LoadAssets();

        // Create paddles and ball
        // Calculate positions based on screen dimensions
        _player1 = std::make_shared<Paddle>(width * 0.05f, height / 2.0f - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, false, height);
        _player2 = std::make_shared<Paddle>(width * 0.95f - PADDLE_WIDTH, height / 2.0f - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED, true, height);
    
        _gameObjectManager.AddObject(_player1);
        _gameObjectManager.AddObject(_player2);

        SpawnBall();
        UpdateScoreTextures(_renderer);

        RegisterListener(EVENT_BALL_BOUNCE,
            [this](const Event& event) { this->OnBallBounce(event); });
    
        return true;
    }

    void PongGame::Update()
    {
        GameEngine::Update();

        if(!_ball || !_player1 || !_player2) return;

        // Check for collisions
        if (Collision2D::CheckCollision(_ball->GetRect(), _player1->GetRect())) {
            // Handle collision with player1
            const auto newPos = Vector2D(_player1->GetPosition().x + _player1->GetWidth(), _ball->GetPosition().y);
            HandleBallPaddleCollision(newPos);
        }
        if (Collision2D::CheckCollision(_ball->GetRect(), _player2->GetRect())) {
            // Handle collision with player2
            const auto newPos = Vector2D(_player2->GetPosition().x - _ball->GetWidth(), _ball->GetPosition().y);
            HandleBallPaddleCollision(newPos);
        }

        BallCheckHorizontalExit();
    }

    void PongGame::RenderObjects()
    {
        DrawNet(_renderer);
        DrawScore(_renderer);
        GameEngine::RenderObjects();
    }

    void PongGame::LoadAssets()
    {
        //Audio
        _audioManager.LoadSound(AUDIO_HIT, "assets/audio/hit.wav");
        _audioManager.LoadSound(AUDIO_SCORE, "assets/audio/score.wav");
        //Fonts
        _textManager.LoadFont(FONT_SCORE, "assets/fonts/DS-DIGIT.ttf", 100.0f);
    }

    void PongGame::UpdateScoreTextures(SDL_Renderer* renderer)
    {
        if (_scoreTexturePlayer1) SDL_DestroyTexture(_scoreTexturePlayer1);
        if (_scoreTexturePlayer2) SDL_DestroyTexture(_scoreTexturePlayer2);

        constexpr SDL_Color color = {255, 255, 255};
        _scoreTexturePlayer1 = _textManager.CreateTextSurface(FONT_SCORE, std::to_string(_scorePlayer1.GetScore()), color, renderer);
        _scoreTexturePlayer2 = _textManager.CreateTextSurface(FONT_SCORE, std::to_string(_scorePlayer2.GetScore()), color, renderer);
        _scoreTextWidthPlayer1 = static_cast<float>(_scoreTexturePlayer1->w);
        _scoreTextHeightPlayer1 = static_cast<float>(_scoreTexturePlayer1->h);
        _scoreTextWidthPlayer2 = static_cast<float>(_scoreTexturePlayer2->w);
        _scoreTextHeightPlayer2 = static_cast<float>(_scoreTexturePlayer2->h);
    }

    void PongGame::DrawNet(SDL_Renderer* renderer) const
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Draw the net
        for (int y = 0; y < _screenHeight; y += NET_HEIGHT + NET_SPACING)
        {
            SDL_FRect netRect = {
                _screenWidth / 2.0f - NET_WIDTH / 2.0f,
                static_cast<float>(y),
                static_cast<float>(NET_WIDTH),
                static_cast<float>(NET_HEIGHT)
            };
            SDL_RenderFillRect(renderer, &netRect);
        }
    }

    void PongGame::DrawScore(SDL_Renderer* renderer) const
    {
        const SDL_FRect dstRectPlayer1 = {50.0f, 50.0f, _scoreTextWidthPlayer1, _scoreTextHeightPlayer1};
        const SDL_FRect dstRectPlayer2 = {_screenWidth - 100.0f, 50.0f, _scoreTextWidthPlayer2, _scoreTextHeightPlayer2};
    
        if (_scoreTexturePlayer1 != nullptr) {
            _textManager.RenderText(renderer, _scoreTexturePlayer1, nullptr, &dstRectPlayer1);
        }
        if (_scoreTexturePlayer2 != nullptr) {
            _textManager.RenderText(renderer, _scoreTexturePlayer2, nullptr, &dstRectPlayer2);
        }
    }


    void PongGame::SpawnBall()
    {
        if(_ball) _gameObjectManager.RemoveObject(_ball);

        int xDirection = Random::GetRandomNumber(0, 1);
        xDirection = xDirection == 0 ? -1 : xDirection;
        float speedX = Random::GetRandomNumber(BALL_MIN_SPEED_X, BALL_MAX_SPEED_X);
        speedX *= static_cast<float>(xDirection);

        float speedY = Random::GetRandomNumber(BALL_MIN_SPEED_Y, BALL_MAX_SPEED_Y);
    
        _ball = std::make_shared<Ball>(_screenWidth / 2.0f, _screenHeight / 2.0f, BALL_SIZE, speedX, speedY,
            _screenWidth, _screenHeight);
        _gameObjectManager.AddObject(_ball);
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    void PongGame::HandleBallPaddleCollision(const Vector2D& newPos)
    {
        _ball->FlipHorizontalMovement();
        auto ballSpeed = _ball->GetSpeed();
        ballSpeed.x += ballSpeed.x * 0.06f;
        ballSpeed.y += ballSpeed.x * 0.03f;
        _ball->SetSpeed(ballSpeed);
        _ball->SetPos(newPos);
        std::cout << "Ball Speed: [" << _ball->GetSpeed().x << ", " << _ball->GetSpeed().y << "]" << std::endl;
    }

    void PongGame::BallCheckHorizontalExit()
    {
        if(!_ball) return;

        if (_ball->GetPosition().x + _ball->GetSize() > 0 && _ball->GetPosition().x < _screenWidth)
            return;

        if (_ball->GetPosition().x <= 0)
        {
            _scorePlayer2.IncreaseScore();
            _audioManager.PlaySound(AUDIO_SCORE);
        }
        else if (_ball->GetPosition().x >= _screenWidth)
        {
            _scorePlayer1.IncreaseScore();
            _audioManager.PlaySound(AUDIO_SCORE);
        }

        std::cout << "Player 1 Score: " << _scorePlayer1.GetScore() << std::endl;
        std::cout << "Player 2 Score: " << _scorePlayer2.GetScore() << std::endl;
        SpawnBall();
        UpdateScoreTextures(_renderer);
    }

    void PongGame::OnBallBounce(const Event& event)
    {
        _audioManager.PlaySound(AUDIO_HIT);
    }
}