#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

struct SpriteFrame {
    SDL_FRect SrcRect;  // Position and size of the frame within the sprite sheet
};

class Image {
public:
    static bool Init();
    //Single Image
    void LoadTexture(const std::string& name, const std::string& path, SDL_Renderer* renderer);
    SDL_Texture* GetTexture(const std::string& name) const;
    //SpriteSheets
    void LoadSpriteSheet(const std::string& name, const std::string& path, int spriteWidth, int spriteHeight, SDL_Renderer* renderer);
    const SDL_FRect* GetSprite(const std::string& name, int frame) const;

    virtual void Clean();

protected:
    std::unordered_map<std::string, SDL_Texture*> _textures;
    std::unordered_map<std::string, std::vector<SpriteFrame>> _spriteFrames;//storing the sprites of a sprite sheet
};