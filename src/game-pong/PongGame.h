#pragma once

#include "GameEngine.h"
#include "Ball.h"
#include "Paddle.h"
#include "Score.h"


class PongGame final : public GameEngine
{
public:
    PongGame();
    bool Init(const char* title, int width, int height) override;
    void Update() override;
    void RenderObjects() override;

private:
    void LoadAssets();
    void UpdateScoreTextures(SDL_Renderer* renderer);
    void DrawNet(SDL_Renderer* renderer) const;
    void DrawScore(SDL_Renderer* renderer) const;
    void SpawnBall();
    void HandleBallPaddleCollision(const Vector2D& newPos);
    void BallCheckHorizontalExit();
    void OnBallBounce(const Event& event);

    // Game Configuration
    // Paddle Configuration
    const float PADDLE_WIDTH = 10.0f;
    const float PADDLE_HEIGHT = 100.0f;
    const float PADDLE_SPEED = 350.0f;
    //Ball Configuration
    const float BALL_MIN_SPEED_X = 250.0f;
    const float BALL_MAX_SPEED_X = 450.0f;
    const float BALL_MIN_SPEED_Y = 150.0f;
    const float BALL_MAX_SPEED_Y = 300.0f;
    const float BALL_SIZE = 10.0f;
    // Net configuration
    const int NET_WIDTH = 7; // Width of each rectangle in the net
    const int NET_HEIGHT = 30; // Height of each rectangle in the net
    const int NET_SPACING = 20; // Space between each rectangle in the net
    // Audio
    const char* AUDIO_HIT = "audioHit";
    const char* AUDIO_SCORE = "audioScore";
    // Font
    const char* FONT_SCORE = "fontScore"; 

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