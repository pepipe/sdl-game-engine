#pragma once

namespace Pong
{
    // Paddle Configuration
    constexpr float PADDLE_WIDTH = 10.0f;
    constexpr float PADDLE_HEIGHT = 100.0f;
    constexpr float PADDLE_SPEED = 350.0f;
    //Ball Configuration
    constexpr float BALL_MIN_SPEED_X = 250.0f;
    constexpr float BALL_MAX_SPEED_X = 450.0f;
    constexpr float BALL_MIN_SPEED_Y = 150.0f;
    constexpr float BALL_MAX_SPEED_Y = 300.0f;
    constexpr float BALL_SIZE = 10.0f;
    // Net configuration
    constexpr int NET_WIDTH = 7; // Width of each rectangle in the net
    constexpr int NET_HEIGHT = 30; // Height of each rectangle in the net
    constexpr int NET_SPACING = 20; // Space between each rectangle in the net
    // Audio
    inline auto AUDIO_HIT = "audioHit";
    inline auto AUDIO_SCORE = "audioScore";
    // Font
    inline auto FONT_SCORE = "fontScore";
}