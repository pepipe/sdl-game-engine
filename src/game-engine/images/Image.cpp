#include "Image.h"

#include <ranges>
#include <SDL3_image/SDL_image.h>

namespace GameEngine::Images
{
    bool Image::Init()
    {
        if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == false)
        {
            SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
            return false;
        }

        return true;
    }

    void Image::LoadTexture(const std::string& name, const std::string& path, SDL_Renderer* renderer)
    {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface)
        {
            SDL_Log("Failed to load image %s: %s", path.c_str(), SDL_GetError());
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
    }

    SDL_Texture* Image::GetTexture(const std::string& name) const
    {
        if (const auto it = _textures.find(name); it != _textures.end())
        {
            return it->second;
        }
        return nullptr;
    }


    void Image::Clean()
    {
        for (const auto texture : _textures | std::views::values)
        {
            SDL_DestroyTexture(texture);
        }
        _textures.clear();
        IMG_Quit();
    }
}