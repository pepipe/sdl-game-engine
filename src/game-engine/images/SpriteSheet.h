#pragma once

#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>

namespace GameEngine::Images
{
    struct SpriteFrame
    {
        SDL_FRect SrcRect; // Position and size of the frame within the sprite sheet
    };

    class SpriteSheet final
    {
    public:
        static bool Init();
        void LoadSpriteSheet(const std::string& name, const std::string& path, int spriteWidth, int spriteHeight,
                             SDL_Renderer* renderer);
        SDL_Texture* GetTexture(const std::string& name) const;
        bool GetTextureSize(const std::string& name, float& width, float& height) const;
        const SDL_FRect* GetSpriteFRect(const std::string& name, int frame) const;
        void Clean();

    private:
        std::unordered_map<std::string, SDL_Texture*> _textures;
        std::unordered_map<std::string, std::vector<SpriteFrame>> _spriteFrames; //storing the sprites of a sprite sheet
    };
}