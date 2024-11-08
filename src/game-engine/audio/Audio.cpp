#include "Audio.h"

#include <ranges>

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

void Audio::PlaySound(const std::string& name, const int loops, const int volume)
{
    if (const auto it = _sounds.find(name); it != _sounds.end())
    {
        Mix_VolumeChunk(it->second, volume);
        Mix_PlayChannel(-1, it->second, loops);
    }
}

void Audio::LoadMusic(const std::string& path)
{
    _music = Mix_LoadMUS(path.c_str());
}

void Audio::PlayMusic(const int loops, const int volume) const
{
    Mix_VolumeMusic(volume);
    Mix_PlayMusic(_music, loops);
}

void Audio::SetMasterVolume(const int volume)
{
    Mix_MasterVolume(volume);
}

void Audio::Clean()
{
    for (const auto sounds : _sounds | std::views::values)
    {
        Mix_FreeChunk(sounds);
    }
    _sounds.clear();
    if(_music != nullptr)
        Mix_FreeMusic(_music);
    Mix_CloseAudio();
    Mix_Quit();
}
