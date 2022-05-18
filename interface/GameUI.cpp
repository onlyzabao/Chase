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
    if (!Mixer::loadSound())
    {
        return false;
    }
    return true;
}

void GameUI::initMainMenuButton()
{
    button[ButtonType::START_BUTTON].setSize({256, 64});
    button[ButtonType::OPTIONS_BUTTON].setSize({256, 64});
    button[ButtonType::EXIT_BUTTON].setSize({256, 64});

    button[ButtonType::START_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 400});
    button[ButtonType::OPTIONS_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 500});
    button[ButtonType::EXIT_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 600});
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
            button[ButtonType::OPTIONS_BUTTON].handleEvent(&event);
            button[ButtonType::EXIT_BUTTON].handleEvent(&event);
            if (button[ButtonType::START_BUTTON].isClicked())
            {
                _status = Status::BEGIN_STATUS;
            }
            else if (button[ButtonType::OPTIONS_BUTTON].isClicked())
            {
                _status = Status::OPTION_STATUS;
            }
            else if (button[ButtonType::EXIT_BUTTON].isClicked())
            {
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
    }
}

void GameUI::initMiniMenuButton()
{
    button[ButtonType::START_BUTTON].setSize({256, 64});
    button[ButtonType::EXIT_BUTTON].setSize({256, 64});

    button[ButtonType::START_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 500});
    button[ButtonType::EXIT_BUTTON].setPosition({(SCREEN_WIDTH - button[ButtonType::START_BUTTON].getSize().w) / 2, 600});
}

void GameUI::handleMiniMenuEvent(Status &_status)
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
            button[ButtonType::EXIT_BUTTON].handleEvent(&event);
            if (button[ButtonType::START_BUTTON].isClicked())
            {
                _status = Status::BEGIN_STATUS;
            }
            else if (button[ButtonType::EXIT_BUTTON].isClicked())
            {
                _status = Status::EXIT_STATUS;
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

bool GameUI::isQuit() const
{
    return quit;
}

void GameUI::exit()
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
