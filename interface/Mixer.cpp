#include "Mixer.h"

Mixer::~Mixer()
{
    free();
}

bool Mixer::init()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Unable to initialize SDL_mixer. Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

bool Mixer::load()
{
    music[Music::CHASING_MUSIC] = Mix_LoadMUS("./asset/wav/chasing.wav");
    if (music[Music::CHASING_MUSIC] == nullptr)
    {
        std::cout << "Unable to load chasing music. Error: " << Mix_GetError() << std::endl;
        return false;
    }
    Mix_VolumeMusic(MUSIC_DEFAULT_VOLUME);

    sound[Sound::EXPLOSION_SOUND] = Mix_LoadWAV("./asset/wav/explosion.wav");
    if (sound[Sound::EXPLOSION_SOUND] == nullptr)
    {
        std::cout << "Unable to load explosion sound. Error: " << Mix_GetError() << std::endl;
        return false;
    }
    sound[Sound::TRACKED_SOUND] = Mix_LoadWAV("./asset/wav/tracked.wav");
    if (sound[Sound::TRACKED_SOUND] == nullptr)
    {
        std::cout << "Unable to load tracked sound. Error: " << Mix_GetError() << std::endl;
        return false;
    }
    sound[Sound::BUTTON_SOUND] = Mix_LoadWAV("./asset/wav/button.wav");
    if (sound[Sound::BUTTON_SOUND] == nullptr)
    {
        std::cout << "Unable to load button sound. Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void Mixer::free()
{
    for (auto item : music)
    {
        Mix_FreeMusic(item);
        item = nullptr;
    }

    for (auto item : sound)
    {
        Mix_FreeChunk(item);
        item = nullptr;
    }
}

void Mixer::playSound(const Sound &_chunk) const
{
    Mix_PlayChannel(-1, sound[_chunk], 0);
}

void Mixer::playMusic(const Music &_track) const
{
    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();
    }
    Mix_PlayMusic(music[_track], -1);
}

void Mixer::pauseMusic() const
{
    if (!Mix_PausedMusic())
    {
        Mix_PauseMusic();
    }
}

void Mixer::resumeMusic() const
{
    if(Mix_PausedMusic())
    {
        Mix_ResumeMusic();
    }
}

void Mixer::stopMustic() const
{
    Mix_HaltMusic();
}