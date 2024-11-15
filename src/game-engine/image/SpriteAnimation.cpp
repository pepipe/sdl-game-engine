#include "SpriteAnimation.h"

namespace GameEngine::Image
{
    SpriteAnimation::SpriteAnimation(const std::string& spriteName, const int totalFrames, const float framesPerSecond) :
        _imageName(spriteName),
        _totalFrames(totalFrames)
    {
        _frameDuration = 1.0f / framesPerSecond;
    }

    void SpriteAnimation::Update(const float deltaTime)
    {
        _elapsedTime += deltaTime;
        if (_elapsedTime >= _frameDuration)
        {
            _elapsedTime = 0;
            _currentFrame = (_currentFrame + 1) % _totalFrames;
        }
    }


    int SpriteAnimation::GetCurrentFrame() const
    {
        return _currentFrame;
    }

    std::string SpriteAnimation::GetSpriteName() const
    {
        return _imageName;
    }
}