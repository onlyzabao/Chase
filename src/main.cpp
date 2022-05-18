#include "../core/GameEngine.h"
#include "../interface/GameUI.h"

void runGuideMenu(GameUI *_p_gameUI)
{
    // Guide menu
    _p_gameUI->initGuideMenuButton();
    Status status = Status::BEGIN_STATUS;
    while (status != Status::EXIT_STATUS && !_p_gameUI->isQuit())
    {
        _p_gameUI->handleGuideMenuEvent(status);
        _p_gameUI->clear();
        _p_gameUI->drawBackground();
        _p_gameUI->drawGuideMenu(_p_gameUI->getButtonMap());
        _p_gameUI->present();
    }
    _p_gameUI->initMainMenuButton();
}

void runMiniMenu(GameUI *_p_gameUI, Status &_status, const Player &_winner)
{
    // Mini menu & Winner display
    _p_gameUI->initMiniMenuButton();
    while ((_status == Status::END_STATUS || _status == Status::PAUSE_STATUS) && !_p_gameUI->isQuit())
    {
        _p_gameUI->handleMiniMenuEvent(_status);
        _p_gameUI->clear();
        _p_gameUI->drawBackground();
        _p_gameUI->drawMiniMenu(_winner, _p_gameUI->getButtonMap());
        _p_gameUI->present();
    }
}

void runStartMenu(GameUI *_p_gameUI)
{
    _p_gameUI->initStartMenuButton();
    Status status = Status::BEGIN_STATUS;
    while (status != Status::END_STATUS && !_p_gameUI->isQuit())
    {
        _p_gameUI->handleStartMenuEvent(status);
        _p_gameUI->clear();
        _p_gameUI->drawBackground();
        _p_gameUI->drawStartMenu(_p_gameUI->getButtonMap());
        _p_gameUI->present();
    }
}

void runGame(GameUI *_p_gameUI)
{
    runStartMenu(_p_gameUI);

    GameEngine *p_gameEngine = new GameEngine(_p_gameUI->getPlayerNumber());
    p_gameEngine->init(_p_gameUI->getMovementKey(), _p_gameUI->getShootingKey());

    _p_gameUI->playMusic(Music::CHASING_MUSIC);
    Status status = Status::RUNNING_STATUS;
    while (status != Status::EXIT_STATUS && !_p_gameUI->isQuit())
    {
        _p_gameUI->handlePlaygroundEvent(status);
        if (status == Status::RUNNING_STATUS)
        {
            // Playing game
            p_gameEngine->handleMovement(_p_gameUI);
            p_gameEngine->handleCollision(_p_gameUI);
            p_gameEngine->draw(_p_gameUI);
            p_gameEngine->updateStatus(status);
        }
        else if (status == Status::BEGIN_STATUS)
        {
            // Restart game
            delete p_gameEngine;
            p_gameEngine = new GameEngine(_p_gameUI->getPlayerNumber());
            p_gameEngine->init(_p_gameUI->getMovementKey(), _p_gameUI->getShootingKey());
            _p_gameUI->playMusic(Music::CHASING_MUSIC);
            status = Status::RUNNING_STATUS;
        }
        else if (status == Status::END_STATUS || status == Status::PAUSE_STATUS)
        {
            // Pause & End game
            _p_gameUI->pauseMusic();
            runMiniMenu(_p_gameUI, status, p_gameEngine->getWinner());
            _p_gameUI->resumeMusic();
        }
    }
    delete p_gameEngine;
    _p_gameUI->stopMustic();
    _p_gameUI->initMainMenuButton();
}

int main(int argc, char *argv[])
{
    // Initialize user interface
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
                // Main menu
                p_gameUI->handleMainMenuEvent(status);
                if (status == Status::BEGIN_STATUS)
                {
                    // Playground
                    runGame(p_gameUI);
                    status = Status::NONE_STATUS;
                }
                else if (status == Status::GUIDE_STATUS)
                {
                    // Setting
                    runGuideMenu(p_gameUI);
                    status = Status::NONE_STATUS;
                }
                else if (status == Status::EXIT_STATUS)
                {
                    // Exit
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