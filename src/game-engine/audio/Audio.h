#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include <string>
#include <unordered_map>

class Audio
{
public:
    static bool Init(SDL_AudioDeviceID deviceId, const SDL_AudioSpec* desiredSpec);
    void LoadSound(const std::string& name, const std::string& path);
    void PlaySound(const std::string& name, int loops = 0, int volume = MIX_MAX_VOLUME);
    void LoadMusic(const std::string& path);
    void PlayMusic(int loops = 0, int volume = MIX_MAX_VOLUME) const;
    static void SetMasterVolume(int volume);
    void Clean();

private:
    std::unordered_map<std::string, Mix_Chunk*> _sounds;
    Mix_Music* _music = nullptr;
};
