#include "../core/GameEngine.h"
#include "../interface/GameUI.h"

int playerNumber = MAX_PLAYERS_NUMER;

std::vector<Coordinate> startPosition = {
    {SCREEN_WIDTH / 4 - SPACESHIP_WIDTH / 2, (SCREEN_HEIGHT * 3) / 4 - SPACESHIP_HEIGHT / 2},
    {(SCREEN_WIDTH * 3) / 4 - SPACESHIP_WIDTH / 2, (SCREEN_HEIGHT * 3) / 4 - SPACESHIP_HEIGHT / 2},
    {SCREEN_WIDTH / 4 - SPACESHIP_WIDTH / 2, SCREEN_HEIGHT / 4 - SPACESHIP_HEIGHT / 2},
    {(SCREEN_WIDTH * 3) / 4 - SPACESHIP_WIDTH / 2, SCREEN_HEIGHT / 4 - SPACESHIP_HEIGHT / 2},
};

std::vector<MovementControl> moveControl = {
    {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D},
    {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT},
    {SDL_SCANCODE_Y, SDL_SCANCODE_H, SDL_SCANCODE_G, SDL_SCANCODE_J},
    {SDL_SCANCODE_P, SDL_SCANCODE_SEMICOLON, SDL_SCANCODE_L, SDL_SCANCODE_APOSTROPHE}
};

ShootingControl shotControl =
{
    SDL_SCANCODE_R,
    SDL_SCANCODE_SLASH,
    SDL_SCANCODE_I,
    SDL_SCANCODE_RIGHTBRACKET
};

void runOptionMenu(GameUI *_p_gameUI);
void runMiniMenu(GameUI *_p_gameUI, Status &_status, const Player &_winner);
void runGame(GameUI *_p_gameUI);

int main(int argc, char *argv[])
{
    GameUI gameUI;
    GameUI *const p_gameUI = &gameUI;
    if (p_gameUI->init())
    {
        if (p_gameUI->loadTexture() && p_gameUI->loadSound())
        {
            Status status = Status::NONE_STATUS;
            p_gameUI->initMainMenuButton();
            while (!p_gameUI->isQuit())
            {
                p_gameUI->handleMainMenuEvent(status);
                if (status == Status::BEGIN_STATUS)
                {
                    runGame(p_gameUI);
                    status = Status::NONE_STATUS;
                }
                else if (status == Status::OPTION_STATUS)
                {
                    runOptionMenu(p_gameUI);
                    status = Status::NONE_STATUS;
                }
                else if (status == Status::EXIT_STATUS)
                {
                    p_gameUI->exit();
                }
                p_gameUI->clear();
                p_gameUI->drawBackground();
                p_gameUI->drawMainMenu(p_gameUI->getButtonMap());
                p_gameUI->present();
            }
        }
    }
    p_gameUI->free();
    return 0;
}

void runOptionMenu(GameUI *_p_gameUI)
{

}

void runGame(GameUI *_p_gameUI)
{
    GameEngine *p_gameEngine = new GameEngine(playerNumber);
    p_gameEngine->init(startPosition, moveControl, shotControl);

    Status status = Status::RUNNING_STATUS;
    while (status != Status::EXIT_STATUS && !_p_gameUI->isQuit())
    {
        _p_gameUI->handlePlaygroundEvent(status);
        if (status == Status::RUNNING_STATUS)
        {
            p_gameEngine->handleMovement(_p_gameUI);
            p_gameEngine->handleCollision(_p_gameUI);
            p_gameEngine->draw(_p_gameUI);
            p_gameEngine->updateStatus(status);
        }
        else if (status == Status::BEGIN_STATUS)
        {
            delete p_gameEngine;
            p_gameEngine = new GameEngine(playerNumber);
            p_gameEngine->init(startPosition, moveControl, shotControl);
            status = Status::RUNNING_STATUS;
        }
        else if (status == Status::END_STATUS)
        {
            runMiniMenu(_p_gameUI, status, p_gameEngine->getWinner());
        }
    }
    delete p_gameEngine;
}

void runMiniMenu(GameUI *_p_gameUI, Status &_status, const Player &_winner)
{
    _p_gameUI->initMiniMenuButton();
    while (_status == Status::END_STATUS && !_p_gameUI->isQuit())
    {
        _p_gameUI->handleMiniMenuEvent(_status);
        _p_gameUI->clear();
        _p_gameUI->drawBackground();
        _p_gameUI->drawMiniMenu(_winner, _p_gameUI->getButtonMap());
        _p_gameUI->present();
    }
}

