#pragma once
#include <SDL_mixer.h>
#include <string>

class Audio
{
public:
    Audio();
    ~Audio();

    bool Init(int frequency = 44100, Uint16 format = SDL_AUDIO_S16, int channels = 2, int chunkSize = 4096);
    void LoadSound(const std::string& name, const std::string& path);
    void PlaySound(const std::string& name, int loops = 0);
    void CleanUp();
private:
};
