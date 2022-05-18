#pragma once
#include "Painter.h"
#include "Mixer.h"

class GameUI : public Painter, public Mixer
{
public:
    GameUI() : Painter(), Mixer()
    {
        p_window = nullptr;
        quit = false;

        button = std::vector<Button>(ButtonType::TOTAL_BUTTONS, Button());
    }
    ~GameUI();

    bool init();

    bool loadTexture();
    bool loadSound();

    void free();

    const Uint8 *getKeyState() const;
    std::vector<Button> getButtonMap() const;
    bool isQuit() const;
    void exit();

    void initMainMenuButton();
    void handleMainMenuEvent(Status &_status);

    void initMiniMenuButton();
    void handleMiniMenuEvent(Status &_status);
    
    void handlePlaygroundEvent(Status &_status);

    void clear() const;
    void present() const;

private:
    SDL_Window *p_window;

    SDL_Event event;
    bool quit;

    std::vector<Button> button;
};