#include "Text.h"

bool Text::Init()
{
    return TTF_Init();
}

bool Text::LoadFont(const std::string& name, const std::string& path, const float size)
{
    TTF_Font* font = TTF_OpenFont(path.c_str(), size);
    if (!font)
    {
        // Handle error
        return false;
    }
    _fonts[name] = font;
    return true;
}

SDL_Texture* Text::RenderText(const std::string& fontName, const std::string& text, const SDL_Color color, SDL_Renderer* renderer)
{
    TTF_Font* font = _fonts[fontName];
    if (!font) return nullptr;
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), text.length(), color);
    if (!surface) return nullptr;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface); // Free the surface after creating the texture
    return texture;
}

void Text::Clean()
{
    for (const auto& pair : _fonts)
    {
        TTF_CloseFont(pair.second);
    }
    _fonts.clear();
    TTF_Quit();
}