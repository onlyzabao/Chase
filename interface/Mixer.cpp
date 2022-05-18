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

bool Mixer::loadSound()
{
    playgroundSound[Sound::EXPLOSION_SOUND] = Mix_LoadWAV("./asset/wav/explosion.wav");
    if (playgroundSound[Sound::EXPLOSION_SOUND] == nullptr)
    {
        std::cout << "Unable to load explosion sound. Error: " << Mix_GetError() << std::endl;
        return false;
    }
    playgroundSound[Sound::TRACKED_SOUND] = Mix_LoadWAV("./asset/wav/tracked.wav");
    if (playgroundSound[Sound::TRACKED_SOUND] == nullptr)
    {
        std::cout << "Unable to load tracked sound. Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void Mixer::free()
{
    for (auto sound : playgroundSound)
    {
        Mix_FreeChunk(sound);
        sound = nullptr;
    }
}

void Mixer::playSound(const Sound &_sound) const
{
    Mix_PlayChannel(-1, playgroundSound[_sound], 0);
}