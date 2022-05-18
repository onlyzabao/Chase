#pragma once
#include "../core/GameHeader.h"
#include <SDL_mixer.h>

class Mixer
{
public:
    Mixer()  
    {
        playgroundSound = std::vector<Mix_Chunk *>(Sound::TOTAL_SOUNDS, nullptr);
    }
    ~Mixer();

    bool init();
    bool loadSound();
    void free();

    void playSound(const Sound &_sound) const;

protected:
    std::vector<Mix_Chunk *> playgroundSound;
};