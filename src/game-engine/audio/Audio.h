#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <unordered_map>

class Audio
{
public:
    ~Audio();

    static bool InitializeAudio(SDL_AudioDeviceID deviceId, const SDL_AudioSpec* desiredSpec);
    void LoadSound(const std::string& name, const std::string& path);
    void PlaySound(const std::string& name, int loops = 0);
    void CleanUp();

private:
    std::unordered_map<std::string, Mix_Chunk*> _sounds;
};
