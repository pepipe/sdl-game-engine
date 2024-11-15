#include "SpriteSheet.h"

#include <ranges>
#include <SDL3_image/SDL_image.h>

namespace GameEngine::Images
{
    bool SpriteSheet::Init()
    {
        if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == false)
        {
            SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
            return false;
        }

        return true;
    }

    void SpriteSheet::LoadSpriteSheet(const std::string& name, const std::string& path, const int spriteWidth,
                                      const int spriteHeight, SDL_Renderer* renderer)
    {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface)
        {
            SDL_Log("Failed to load sprite sheet %s: %s", path.c_str(), SDL_GetError());
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
        if (!texture)
        {
            SDL_Log("Failed to create texture: %s", SDL_GetError());
            return;
        }
        _textures[name] = texture;

        // Split the sprite sheet into frames
        float sheetWidth, sheetHeight;
        SDL_GetTextureSize(texture, &sheetWidth, &sheetHeight);

        std::vector<SpriteFrame> frames;
        for (int y = 0; y < sheetHeight; y += spriteHeight)
        {
            for (int x = 0; x < sheetWidth; x += spriteWidth)
            {
                frames.push_back({
                    SDL_FRect{
                        static_cast<float>(x), static_cast<float>(y), static_cast<float>(spriteWidth),
                        static_cast<float>(spriteHeight)
                    }
                });
            }
        }
        _spriteFrames[name] = frames;
    }

    SDL_Texture* SpriteSheet::GetTexture(const std::string& name) const
    {
        if (const auto it = _textures.find(name); it != _textures.end())
        {
            return it->second;
        }
        return nullptr;
    }

    const SDL_FRect* SpriteSheet::GetSpriteFRect(const std::string& name, const int frame) const
    {
        if (const auto it = _spriteFrames.find(name); it != _spriteFrames.end() && frame < it->second.size())
        {
            return &it->second[frame].SrcRect;
        }
        return nullptr;
    }

    void SpriteSheet::Clean()
    {
        for (const auto texture : _textures | std::views::values)
        {
            SDL_DestroyTexture(texture);
        }
        _textures.clear();
        _spriteFrames.clear();
        IMG_Quit();
    }
}