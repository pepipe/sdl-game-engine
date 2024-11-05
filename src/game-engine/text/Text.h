#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

class Text
{
public:
    static bool Init();
    bool LoadFont(const std::string& name, const std::string& path, float size);
    SDL_Texture* RenderText(const std::string& fontName, const std::string& text, SDL_Color color, SDL_Renderer* renderer);
    void Clean();

private:
    std::unordered_map<std::string, TTF_Font*> _fonts;
};
