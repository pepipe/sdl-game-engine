#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

class Text
{
public:
    bool Init();

    // Load a font
    bool LoadFont(const std::string& name, const std::string& path, int size);

    // Render text and return the texture
    SDL_Texture* RenderText(const std::string& fontName, const std::string& text, SDL_Color color, SDL_Renderer* renderer);

    // Clean up loaded fonts
    void Clean();

private:
    // Store loaded fonts
    std::unordered_map<std::string, TTF_Font*> _fonts;
};
