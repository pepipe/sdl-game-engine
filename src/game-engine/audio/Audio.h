#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <unordered_map>

class Audio
{
public:
    bool Init(SDL_AudioDeviceID deviceId, const SDL_AudioSpec* desiredSpec);
    void LoadSound(const std::string& name, const std::string& path);
    void PlaySound(const std::string& name, int loops = 0);
    void Clean();

private:
    std::unordered_map<std::string, Mix_Chunk*> _sounds;
};
