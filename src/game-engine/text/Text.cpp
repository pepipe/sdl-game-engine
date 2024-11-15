#include "Text.h"

#include <ranges>

namespace GameEngine::Text
{
    bool Text::Init()
    {
        if(TTF_Init() == false)
        {
            SDL_Log("Failed to initialize SDL_ttf: %s", SDL_GetError());
            return false;
        }

        return true;
    }

    bool Text::LoadFont(const std::string& name, const std::string& path, const float size)
    {
        TTF_Font* font = TTF_OpenFont(path.c_str(), size);
        if (!font)
        {
            SDL_Log("Failed to load font %s: %s", path.c_str(), SDL_GetError());
            return false;
        }
        _fonts[name] = font;
        return true;
    }

    SDL_Texture* Text::CreateTextSurface(const std::string& fontName, const std::string& text, const SDL_Color color, SDL_Renderer* renderer)
    {
        TTF_Font* font = _fonts[fontName];
        if (!font)
        {
            SDL_Log("Failed to get font %s: %s", fontName.c_str(), SDL_GetError());
            return nullptr;
        }
    
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
        if (!surface)
        {
            SDL_Log("Failed to create surface from TTF %s: %s", fontName, SDL_GetError());
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface); // Free the surface after creating the texture
        return texture;
    }

    bool Text::RenderText(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_FRect* srcRect, const SDL_FRect* dstRect)
    {
        return SDL_RenderTexture(renderer, texture, srcRect, dstRect);
    }


    void Text::Clean()
    {
        for (const auto& val : _fonts | std::views::values)
        {
            TTF_CloseFont(val);
        }
        _fonts.clear();
        TTF_Quit();
    }
}
