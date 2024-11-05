#include "Audio.h"

bool Audio::Init(const SDL_AudioDeviceID deviceId, const SDL_AudioSpec* desiredSpec)
{
    if (Mix_OpenAudio(deviceId, desiredSpec) == false)
    {
        SDL_Log("Failed to open audio device: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Audio::LoadSound(const std::string& name, const std::string& path)
{
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (!sound)
    {
        SDL_Log("Failed to load sound %s: %s", path.c_str(), SDL_GetError());
        return;
    }
    _sounds[name] = sound;
}

void Audio::PlaySound(const std::string& name, const int loops)
{
    if (const auto it = _sounds.find(name); it != _sounds.end())
    {
        Mix_PlayChannel(-1, it->second, loops);
    }
}

void Audio::Clean()
{
    for (auto sound : _sounds)
    {
        Mix_FreeChunk(sound.second);
    }
    _sounds.clear();
    Mix_CloseAudio();
    Mix_Quit();
}
