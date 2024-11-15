#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(const float width, const float height, const Vector2D& position, Image& image,
                                 const std::string& spriteName, const std::string& path, SDL_Renderer* renderer,
                                 const int totalFrames, const float framesPerSecond) :
    GameObject2D(width, height, position),
    _image(image),
    _imageName(spriteName),
    _totalFrames(totalFrames)
{
    _frameDuration = 1.0f / framesPerSecond;
    _image.LoadSpriteSheet(_imageName, path, 64, 64, renderer);
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

void SpriteAnimation::Render(SDL_Renderer* renderer) const
{
    const SDL_FRect* srcRect = _image.GetSprite(_imageName, _currentFrame);
    const SDL_FRect dstRect = {100, 100, srcRect->w, srcRect->h};
    SDL_RenderTexture(renderer, _image.GetTexture(_imageName), srcRect, &dstRect);
}
