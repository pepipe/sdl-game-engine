#pragma once
#include <string>

#include "GameObject2D.h"
#include "Image.h"

class SpriteAnimation : public GameObject2D
{
public:
    SpriteAnimation(float width, float height, const Vector2D& position, Image& image, const std::string& spriteName,
                    const std::string& path, SDL_Renderer* renderer, int totalFrames, float framesPerSecond);

    void HandleEvents(const SDL_Event& event) override
    {
    }
    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) const override;

private:
    Image& _image;
    std::string _imageName;
    int _totalFrames;
    float _frameDuration;
    float _elapsedTime = 0.0f;
    int _currentFrame = 0;
};
