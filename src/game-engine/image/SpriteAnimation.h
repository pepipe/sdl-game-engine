#pragma once

#include <string>

namespace GameEngine::Image
{
    class SpriteAnimation
    {
    public:
        SpriteAnimation(const std::string& spriteName, int totalFrames, float framesPerSecond);

        void Update(float deltaTime);
        int GetCurrentFrame() const;
        std::string GetSpriteName() const;

    private:
        std::string _imageName;
        int _totalFrames;
        float _frameDuration;
        float _elapsedTime = 0.0f;
        int _currentFrame = 0;
    };
}