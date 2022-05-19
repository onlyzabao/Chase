#include "GameUI.h"

GameUI::~GameUI()
{
    GameUI::free();
}

bool GameUI::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Unable to initialize SDL. Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled." << std::endl;
        }
        p_window = SDL_CreateWindow("Chase 1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (p_window == nullptr)
        {
            std::cout << "Unable to create window. Error: " << SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            if (TTF_Init() == -1)
            {
                std::cout << "Unable to initialize SDL_ttf. Error: " << TTF_GetError() << std::endl;
                return false;
            }

            if (!Painter::init(p_window))
            {
                return false;
            }
            else
            {
                SDL_SetRenderDrawColor(p_renderer, 255, 255, 255, 255);

                if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
                {
                    std::cout << "Unable to initialize SDL_image. Error: " << IMG_GetError() << std::endl;
                    return false;
                }
            }

            if (!Mixer::init())
            {
                return false;
            }
        }
    }
    return true;
}

void GameUI::free()
{
    Painter::free();
    Mixer::free();
    
    SDL_DestroyWindow(p_window);
    p_window = nullptr;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    exit(0);
}

bool GameUI::loadTexture()
{   
    if (!Painter::loadTexture())
    {
        return false;
    }
    return true;
}

bool GameUI::loadSound()
{
    if (!Mixer::load())
    {
        return false;
    }
    return true;
}

void GameUI::initMainMenuButton()
{
    button[ButtonType::START_BUTTON].setSize({256, 64});
    button[ButtonType::GUIDE_BUTTON].setSize({256, 64});
    button[ButtonType::EXIT_BUTTON].setSize({256, 64});

    button[ButtonType::START_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 400});
    button[ButtonType::GUIDE_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 500});
    button[ButtonType::EXIT_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 600});
                
    button[ButtonType::START_BUTTON].setSprite(Button::SPRITE_DEFAULT);
    button[ButtonType::GUIDE_BUTTON].setSprite(Button::SPRITE_DEFAULT);
    button[ButtonType::EXIT_BUTTON].setSprite(Button::SPRITE_DEFAULT);
}

void GameUI::handleMainMenuEvent(Status &_status)
{
    while (SDL_PollEvent(&event) > 0)
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
        {
            button[ButtonType::START_BUTTON].handleEvent(&event);
            button[ButtonType::GUIDE_BUTTON].handleEvent(&event);
            button[ButtonType::EXIT_BUTTON].handleEvent(&event);
            if (button[ButtonType::START_BUTTON].isClicked())
            {
                playSound(Sound::BUTTON_SOUND);
                _status = Status::BEGIN_STATUS;
            }
            else if (button[ButtonType::GUIDE_BUTTON].isClicked())
            {
                playSound(Sound::BUTTON_SOUND);
                _status = Status::GUIDE_STATUS;
            }
            else if (button[ButtonType::EXIT_BUTTON].isClicked())
            {
                playSound(Sound::BUTTON_SOUND);
                _status = Status::EXIT_STATUS;
            }
        }
    }
}

void GameUI::handlePlaygroundEvent(Status &_status)
{
    while (SDL_PollEvent(&event) > 0)
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                _status = Status::PAUSE_STATUS;
            }
        }
    }
}

void GameUI::initMiniMenuButton()
{
    button[ButtonType::RESTART_BUTTON].setSize({256, 64});
    button[ButtonType::RESUME_BUTTON].setSize({256, 64});
    button[ButtonType::EXIT_BUTTON].setSize({256, 64});

    button[ButtonType::RESUME_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::RESUME_BUTTON].getSize().w) / 2, 400});
    button[ButtonType::RESTART_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::RESTART_BUTTON].getSize().w) / 2, 500});
    button[ButtonType::EXIT_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 600});

    button[ButtonType::RESUME_BUTTON].setSprite(Button::SPRITE_DEFAULT);
    button[ButtonType::RESTART_BUTTON].setSprite(Button::SPRITE_DEFAULT);
    button[ButtonType::EXIT_BUTTON].setSprite(Button::SPRITE_DEFAULT);
}

void GameUI::handleMiniMenuEvent(Status &_status)
{
    if (_status != Status::PAUSE_STATUS)
    {
        button[ButtonType::RESUME_BUTTON].setSprite(Button::SPRITE_DISABLE);
    }

    while (SDL_PollEvent(&event) > 0)
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_ESCAPE && _status == Status::PAUSE_STATUS)
            {
                _status = Status::RUNNING_STATUS;
            }
        }
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (_status == Status::PAUSE_STATUS)
            {
                button[ButtonType::RESUME_BUTTON].handleEvent(&event);
                if (button[ButtonType::RESUME_BUTTON].isClicked())
                {
                    playSound(Sound::BUTTON_SOUND);
                    _status = Status::RUNNING_STATUS;
                }
            }

            button[ButtonType::RESTART_BUTTON].handleEvent(&event);
            button[ButtonType::EXIT_BUTTON].handleEvent(&event);
            if (button[ButtonType::RESTART_BUTTON].isClicked())
            {
                playSound(Sound::BUTTON_SOUND);
                _status = Status::BEGIN_STATUS;
            }
            else if (button[ButtonType::EXIT_BUTTON].isClicked())
            {
                playSound(Sound::BUTTON_SOUND);
                _status = Status::EXIT_STATUS;
            }
        }
    }
}

void GameUI::initGuideMenuButton()
{
    button[ButtonType::EXIT_BUTTON].setSize({256, 64});
    button[ButtonType::EXIT_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 800});
    button[ButtonType::EXIT_BUTTON].setSprite(Button::SPRITE_DEFAULT);
}

void GameUI::handleGuideMenuEvent(Status &_status)
{
    while (SDL_PollEvent(&event) > 0)
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
        {
            button[ButtonType::EXIT_BUTTON].handleEvent(&event);
            if (button[ButtonType::EXIT_BUTTON].isClicked())
            {
                playSound(Sound::BUTTON_SOUND);
                _status = Status::EXIT_STATUS;
            }
        }
    }
}

void GameUI::initStartMenuButton()
{
    button[ButtonType::TWO_PLAYER_BUTTON].setSize({512, 128});
    button[ButtonType::THREE_PLAYER_BUTTON].setSize({512, 128});
    button[ButtonType::FOUR_PLAYER_BUTTON].setSize({512, 128});

    button[ButtonType::TWO_PLAYER_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::TWO_PLAYER_BUTTON].getSize().w) / 2, 300});
    button[ButtonType::THREE_PLAYER_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::THREE_PLAYER_BUTTON].getSize().w) / 2, 500});
    button[ButtonType::FOUR_PLAYER_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::FOUR_PLAYER_BUTTON].getSize().w) / 2, 700});

    button[ButtonType::TWO_PLAYER_BUTTON].setSprite(Button::SPRITE_DEFAULT);
    button[ButtonType::THREE_PLAYER_BUTTON].setSprite(Button::SPRITE_DEFAULT);
    button[ButtonType::FOUR_PLAYER_BUTTON].setSprite(Button::SPRITE_DEFAULT);
}

void GameUI::handleStartMenuEvent(Status &_status)
{
    while (SDL_PollEvent(&event) > 0)
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN)
        {
            button[ButtonType::TWO_PLAYER_BUTTON].handleEvent(&event);
            button[ButtonType::THREE_PLAYER_BUTTON].handleEvent(&event);
            button[ButtonType::FOUR_PLAYER_BUTTON].handleEvent(&event);
            if (button[ButtonType::TWO_PLAYER_BUTTON].isClicked())
            {
                playSound(Sound::BUTTON_SOUND);
                playerNumber = 2;
                _status = Status::END_STATUS;
            }
            else if (button[ButtonType::THREE_PLAYER_BUTTON].isClicked())
            {
                playSound(Sound::BUTTON_SOUND);
                playerNumber = 3;
                _status = Status::END_STATUS;
            }
            else if (button[ButtonType::FOUR_PLAYER_BUTTON].isClicked())
            {
                playSound(Sound::BUTTON_SOUND);
                playerNumber = 4;
                _status = Status::END_STATUS;
            }
        }
    }
}

const Uint8 *GameUI::getKeyState() const
{
    return SDL_GetKeyboardState(nullptr);
}

std::vector<Button> GameUI::getButtonMap() const
{
    return button;
}

std::vector<MovementControl> GameUI::getMovementKey() const
{
    return movementKey;
}

ShootingControl GameUI::getShootingKey() const
{
    return shootintKey;
}

int GameUI::getPlayerNumber() const
{
    return playerNumber;
}

bool GameUI::isQuit() const
{
    return quit;
}

void GameUI::close()
{
    quit = true;
}

void GameUI::clear() const
{
    SDL_SetRenderDrawColor(p_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(p_renderer);
}

void GameUI::present() const
{
    SDL_RenderPresent(p_renderer);
    SDL_Delay(1);
}
