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

        playerNumber = MIN_PLAYERS_NUMBER;
        movementKey =
        {
            {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D},
            {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT},
            {SDL_SCANCODE_Y, SDL_SCANCODE_H, SDL_SCANCODE_G, SDL_SCANCODE_J},
            {SDL_SCANCODE_P, SDL_SCANCODE_SEMICOLON, SDL_SCANCODE_L, SDL_SCANCODE_APOSTROPHE}
        };
        shootintKey =
        {
            SDL_SCANCODE_R,
            SDL_SCANCODE_SLASH,
            SDL_SCANCODE_I,
            SDL_SCANCODE_RIGHTBRACKET
        };
    }
    ~GameUI();

    bool init();

    bool loadTexture();
    bool loadSound();

    void free();

    const Uint8 *getKeyState() const;
    std::vector<Button> getButtonMap() const;
    std::vector<MovementControl> getMovementKey() const;
    ShootingControl getShootingKey() const;
    int getPlayerNumber() const;
    bool isQuit() const;
    void close();

    void initMainMenuButton();
    void handleMainMenuEvent(Status &_status);

    void initMiniMenuButton();
    void handleMiniMenuEvent(Status &_status);
    
    void initGuideMenuButton();
    void handleGuideMenuEvent(Status &_status);

    void initStartMenuButton();
    void handleStartMenuEvent(Status &_status);

    void handlePlaygroundEvent(Status &_status);

    void clear() const;
    void present() const;

private:
    SDL_Window *p_window;

    SDL_Event event;
    bool quit;

    std::vector<Button> button;

    int playerNumber;
    std::vector<MovementControl> movementKey;
    ShootingControl shootintKey;
};