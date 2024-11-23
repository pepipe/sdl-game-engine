#pragma once

#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>

namespace GameEngine::Images
{
    class Image {
    public:
        static bool Init();
        void LoadTexture(const std::string& name, const std::string& path, SDL_Renderer* renderer);
        SDL_Texture* GetTexture(const std::string& name) const;
        bool GetTextureSize(const std::string& name, float& width, float& height) const;
        void Clean();

    protected:
        std::unordered_map<std::string, SDL_Texture*> _textures;
    };
}