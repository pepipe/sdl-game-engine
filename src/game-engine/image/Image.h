#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

class Image {
public:
    static bool Init();
    void LoadTexture(const std::string& name, const std::string& path, SDL_Renderer* renderer);
    SDL_Texture* GetTexture(const std::string& name) const;
    void Clean();

private:
    std::unordered_map<std::string, SDL_Texture*> _textures;
};