#pragma once

#include "GameEngine.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"

namespace Pong
{
    class PongGame final : public GameEngine::GameEngine
    {
    public:
        PongGame();
        bool Init(const char* title, int width, int height) override;

    private:
        void Update() override;
        void RenderObjects() override;

        void LoadAssets();
        void CheckCollisions();
        void UpdateScoreTextures(SDL_Renderer* renderer);
        void DrawNet(SDL_Renderer* renderer) const;
        void DrawScore(SDL_Renderer* renderer) const;
        void SpawnBall();
        void HandleBallPaddleCollision(const Vector2D& newPos);
        void BallCheckHorizontalExit();
        void OnBallBounce(const Event& event);

        Score _scorePlayer1;
        Score _scorePlayer2;
        std::shared_ptr<Paddle> _player1 = nullptr;
        std::shared_ptr<Paddle> _player2 = nullptr;
        std::shared_ptr<Ball> _ball = nullptr;
        Mix_Chunk* _audioHit = nullptr;
        Mix_Chunk* _audioScore = nullptr;
        SDL_Texture* _scoreTexturePlayer1 = nullptr;
        SDL_Texture* _scoreTexturePlayer2 = nullptr;
        float _scoreTextWidthPlayer1;
        float _scoreTextHeightPlayer1;
        float _scoreTextWidthPlayer2;
        float _scoreTextHeightPlayer2;
    };
}