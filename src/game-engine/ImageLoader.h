#pragma once

/*
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <iostream>

inline SDL_Texture* loadTexture(const std::string& filePath, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
*/