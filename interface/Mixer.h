#pragma once
#include "../core/GameHeader.h"
#include <SDL_mixer.h>

class Mixer
{
public:
    static constexpr int MUSIC_DEFAULT_VOLUME = 50;

    Mixer()  
    {
        music = std::vector<Mix_Music *>(Music::TOTAL_MUSICS, nullptr);
        sound = std::vector<Mix_Chunk *>(Sound::TOTAL_SOUNDS, nullptr);
    }
    ~Mixer();

    bool init();
    bool load();
    void free();

    void playMusic(const Music &_track) const;
    void stopMustic() const;
    void pauseMusic() const;
    void resumeMusic() const;
    void playSound(const Sound &_chunk) const;

protected:
    std::vector<Mix_Music *> music;
    std::vector<Mix_Chunk *> sound;
};