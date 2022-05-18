#include "Painter.h"

Painter::~Painter()
{
    free();
}

bool Painter::init(SDL_Window *_p_window)
{
    p_renderer = SDL_CreateRenderer(_p_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (p_renderer == nullptr)
    {
        std::cout << "Unable to create renderer. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    p_titleTextFont = TTF_OpenFont("./asset/ttf/title.ttf", TITLE_TEXT_SIZE);
    if (p_titleTextFont == nullptr)
    {
        std::cout << "Unable to open font. Error: " << TTF_GetError() << std::endl;
        return false;
    }

    p_winnerTextFont = TTF_OpenFont("./asset/ttf/title.ttf", WINNER_TEXT_SIZE);
    if (p_winnerTextFont == nullptr)
    {
        std::cout << "Unable to opne font. Error: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

bool Painter::loadTexture()
{
    // Common texture
    if (!backgroundTexture.loadFromFile(p_renderer, "./asset/png/menu/background.png"))
    {
        std::cout << "Unable to load background texture." << std::endl;
        return false; 
    }
    if (!menuTitleTexture.loadFromRenderedText(p_renderer, p_titleTextFont, "CHASE", MAIN_COLOR))
    {
        std::cout << "Unable to load title texture." << std::endl;
        return false;
    }

    if (!playgroundTexture[ObjectType::ROCKET].loadFromFile(p_renderer, "./asset/png/playground/rocket.png"))
    {
        std::cout << "Unable to load rocket texture." << std::endl;
        return false;
    }
    if (!playgroundTexture[ObjectType::TRACKER].loadFromFile(p_renderer, "./asset/png/playground/tracker.png"))
    {
        std::cout << "Unable to load tracker texture." << std::endl;
        return false;
    }
    if (!playgroundTexture[ObjectType::BARRIER].loadFromFile(p_renderer, "./asset/png/playground/barrier.png"))
    {
        std::cout << "Unable to load barrier texture." << std::endl;
        return false;
    }

    playgroundTexture[ObjectType::BARRIER].setBlendMode(SDL_BLENDMODE_BLEND);
    playgroundTexture[ObjectType::BARRIER].setAlpha(80);
    
    if (!playgroundTexture[ObjectType::SPACESHIP + Player::PLAYER_1].loadFromFile(p_renderer, "./asset/png/playground/spaceship_1.png"))
    {
        std::cout << "Unable to load player 1's spaceship texture." << std::endl;
        return false;
    }
    if (!playgroundTexture[ObjectType::SPACESHIP + Player::PLAYER_2].loadFromFile(p_renderer, "./asset/png/playground/spaceship_2.png"))
    {
        std::cout << "Unable to load player 2's spaceship texture." << std::endl;
        return false;
    }
    if (!playgroundTexture[ObjectType::SPACESHIP + Player::PLAYER_3].loadFromFile(p_renderer, "./asset/png/playground/spaceship_3.png"))
    {
        std::cout << "Unable to load player 3's spaceship texture." << std::endl;
        return false;
    }
    if (!playgroundTexture[ObjectType::SPACESHIP + Player::PLAYER_4].loadFromFile(p_renderer, "./asset/png/playground/spaceship_4.png"))
    {
        std::cout << "Unable to load player 4's spaceship texture." << std::endl;
        return false;
    }
    if (!fateTexture[Player::PLAYER_1].loadFromFile(p_renderer, "./asset/png/playground/fate_1.png"))
    {
        std::cout << "Unable to load fate texture." << std::endl;
        return false;
    }
    if (!fateTexture[Player::PLAYER_2].loadFromFile(p_renderer, "./asset/png/playground/fate_2.png"))
    {
        std::cout << "Unable to load fate texture." << std::endl;
        return false;
    }
    if (!fateTexture[Player::PLAYER_3].loadFromFile(p_renderer, "./asset/png/playground/fate_3.png"))
    {
        std::cout << "Unable to load fate texture." << std::endl;
        return false;
    }
    if (!fateTexture[Player::PLAYER_4].loadFromFile(p_renderer, "./asset/png/playground/fate_4.png"))
    {
        std::cout << "Unable to load fate texture." << std::endl;
        return false;
    }

    // Mini menu texture
    if (!miniMenuTitleTexture[Player::PLAYER_1].loadFromRenderedText(p_renderer, p_winnerTextFont, "PLAYER 1 WIN!", PLAYER_1_COLOR))
    {
        std::cout << "Unable to load winner texture." << std::endl;
        return false;
    }
    if (!miniMenuTitleTexture[Player::PLAYER_2].loadFromRenderedText(p_renderer, p_winnerTextFont, "PLAYER 2 WIN!", PLAYER_2_COLOR))
    {
        std::cout << "Unable to load winner texture." << std::endl;
        return false;
    }
    if (!miniMenuTitleTexture[Player::PLAYER_3].loadFromRenderedText(p_renderer, p_winnerTextFont, "PLAYER 3 WIN!", PLAYER_3_COLOR))
    {
        std::cout << "Unable to load winner texture." << std::endl;
        return false;
    }
    if (!miniMenuTitleTexture[Player::PLAYER_4].loadFromRenderedText(p_renderer, p_winnerTextFont, "PLAYER 4 WIN!", PLAYER_4_COLOR))
    {
        std::cout << "Unable to load winner texture." << std::endl;
        return false;
    }

    if (!buttonTexture[ButtonType::START_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/start_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }
    if (!buttonTexture[ButtonType::OPTIONS_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/options_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }
    if (!buttonTexture[ButtonType::EXIT_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/exit_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }
    return true;
}

void Painter::free()
{
    SDL_DestroyRenderer(p_renderer);
    p_renderer = nullptr;

    TTF_CloseFont(p_titleTextFont);
    p_titleTextFont = nullptr;

    TTF_CloseFont(p_winnerTextFont);
    p_winnerTextFont = nullptr;

    backgroundTexture.free();
    menuTitleTexture.free();

    for (auto texture : fateTexture)
    {
        texture.free();
    }

    for (auto texture : playgroundTexture)
    {
        texture.free();
    }

    for (auto texture : miniMenuTitleTexture)
    {
        texture.free();
    }

    for (auto texture : buttonTexture)
    {
        texture.free();
    }
}

void Painter::drawBackground() const
{
    backgroundTexture.draw(p_renderer, {0, 0});
}


void Painter::drawPlayground(const std::vector<GameObject *> &_map) const
{
    static int frame = 0;
    static int frameCount = 0;

    // Draw barrier
    static constexpr Size barrierSprite = {1400, 700};
    static Coordinate barrierPosition = {100, 100};
    SDL_Rect barrierClip = {_map[ObjectType::BARRIER]->getState() * barrierSprite.w, 0, barrierSprite.w, barrierSprite.h};
    playgroundTexture[ObjectType::BARRIER].draw(p_renderer, barrierPosition, 0.0, &barrierClip);

    // Draw rocket
    static constexpr Size rocketSprite = {128, 128};
    if (_map[ObjectType::ROCKET] != nullptr)
    {
        int rocketState = _map[ObjectType::ROCKET]->getState();
        Coordinate rocketPosition = {0, 0};
        double rocketAngle = 0.0;
        SDL_Rect rocketClip = {rocketState * rocketSprite.w, frame * rocketSprite.h, rocketSprite.w, rocketSprite.h};
        if (rocketState != 1)
        {
            rocketPosition = _map[ObjectType::ROCKET]->getPosition() - (playgroundTexture[ObjectType::ROCKET].getSize() / 3 - _map[ObjectType::ROCKET]->getSize()) / 2;
            rocketAngle = ((_map[ObjectType::ROCKET]->getAngle() + M_PI / 2) * 180) / M_PI;
        }
        else
        {
            rocketPosition = _map[ObjectType::ROCKET]->getPosition();
            if (rocketPosition.y < 0)
            {
                rocketPosition.y = -15;
            }
            if (rocketPosition.y > SCREEN_HEIGHT)
            {
                rocketPosition.y = SCREEN_HEIGHT - 115;
            }
            if (rocketPosition.x < 0)
            {
                rocketPosition.x = -15;
            }
            if (rocketPosition.x > SCREEN_WIDTH)
            {
                rocketPosition.x = SCREEN_WIDTH - 115;
            }
        }
        playgroundTexture[ObjectType::ROCKET].draw(p_renderer, rocketPosition, rocketAngle, &rocketClip);
    }

    // Draw tracker
    if (_map[ObjectType::TRACKER] != nullptr)
    {
        playgroundTexture[ObjectType::TRACKER].draw(p_renderer, _map[ObjectType::TRACKER]->getPosition());
    }

    // Draw spaceships
    static constexpr Size spaceshipSprite = {64, 64};
    static double spaceshipAngle[Player::TOTAL_PLAYERS];
    for (int i = 0; i < _map.size() - TOTAL_DEFAULT_PLAYGROUND_OBJECTS; i++)
    {
        int spaceshipIndex = _map[ObjectType::SPACESHIP + i]->getDriver() + ObjectType::SPACESHIP;
        int spaceshipState = _map[ObjectType::SPACESHIP + i]->getState();
        Coordinate spaceshipPostion = _map[ObjectType::SPACESHIP + i]->getPosition() - (playgroundTexture[spaceshipIndex].getSize() - _map[ObjectType::SPACESHIP + i]->getSize()) / 2;
        spaceshipAngle[i] = ((_map[ObjectType::SPACESHIP + i]->getAngle() + M_PI / 2) * 180) / M_PI;
        SDL_Rect spaceshipClip = {spaceshipState * spaceshipSprite.w, 0, spaceshipSprite.w, spaceshipSprite.h};
        playgroundTexture[spaceshipIndex].draw(p_renderer, spaceshipPostion, spaceshipAngle[i], &spaceshipClip);
    }

    // Calculate frame
    frame = frameCount / 15;
    if (++frameCount >= 45)
    {
        frameCount = 0;
    }
}

void Painter::drawFate(const Player &_driver, const int &_fate) const
{
    static constexpr Coordinate fatePosition[4][3] =
    {
        {{34, SCREEN_HEIGHT - 118}, {34, SCREEN_HEIGHT - 66}, {86, SCREEN_HEIGHT - 66}},
        {{SCREEN_WIDTH - 66, SCREEN_HEIGHT - 118}, {SCREEN_WIDTH - 66, SCREEN_HEIGHT - 66}, {SCREEN_WIDTH - 118, SCREEN_HEIGHT - 66}},
        {{34, 86},{34, 34},{86, 34}},
        {{SCREEN_WIDTH - 66, 86},{SCREEN_WIDTH - 66, 34}, {SCREEN_WIDTH - 118, 34}}
    };

    for (int i = 0; i < _fate; i++)
    {
        fateTexture[_driver].draw(p_renderer, fatePosition[_driver][i], 0.0);
    }
}

void Painter::drawMiniMenu(const Player &_winner, const std::vector<Button> &_buttonMap) const
{
    static Coordinate titlePosition = {(SCREEN_WIDTH - miniMenuTitleTexture[_winner].getSize().w) / 2, (SCREEN_HEIGHT - miniMenuTitleTexture[_winner].getSize().h) / 4};
    miniMenuTitleTexture[_winner].draw(p_renderer, titlePosition);

    int startButtonSprite = _buttonMap[ButtonType::START_BUTTON].getSprite();
    SDL_Rect startButtonClip = 
    {
        _buttonMap[ButtonType::START_BUTTON].getSize().w * startButtonSprite,
        0,
        _buttonMap[ButtonType::START_BUTTON].getSize().w,
        _buttonMap[ButtonType::START_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::START_BUTTON].draw(p_renderer, _buttonMap[ButtonType::START_BUTTON].getPosition(), 0.0, &startButtonClip);

    int exitButtonSprite = _buttonMap[ButtonType::EXIT_BUTTON].getSprite();
    SDL_Rect exitButtonClip = 
    {
        _buttonMap[ButtonType::EXIT_BUTTON].getSize().w * exitButtonSprite,
        0,
        _buttonMap[ButtonType::EXIT_BUTTON].getSize().w,
        _buttonMap[ButtonType::EXIT_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::EXIT_BUTTON].draw(p_renderer, _buttonMap[ButtonType::EXIT_BUTTON].getPosition(), 0.0, &exitButtonClip);
}

void Painter::drawMainMenu(const std::vector<Button> &_buttonMap) const
{
    static Coordinate titlePosition = {(SCREEN_WIDTH - menuTitleTexture.getSize().w) / 2, (SCREEN_HEIGHT - menuTitleTexture.getSize().h) / 6};
    menuTitleTexture.draw(p_renderer, titlePosition);

    int startButtonSprite = _buttonMap[ButtonType::START_BUTTON].getSprite();
    SDL_Rect startButtonClip = 
    {
        _buttonMap[ButtonType::START_BUTTON].getSize().w * startButtonSprite,
        0,
        _buttonMap[ButtonType::START_BUTTON].getSize().w,
        _buttonMap[ButtonType::START_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::START_BUTTON].draw(p_renderer, _buttonMap[ButtonType::START_BUTTON].getPosition(), 0.0, &startButtonClip);

    int optionButtonSprite = _buttonMap[ButtonType::OPTIONS_BUTTON].getSprite();
    SDL_Rect optionButtonClip = 
    {
        _buttonMap[ButtonType::OPTIONS_BUTTON].getSize().w * optionButtonSprite,
        0,
        _buttonMap[ButtonType::OPTIONS_BUTTON].getSize().w,
        _buttonMap[ButtonType::OPTIONS_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::OPTIONS_BUTTON].draw(p_renderer, _buttonMap[ButtonType::OPTIONS_BUTTON].getPosition(), 0.0, &optionButtonClip);

    int exitButtonSprite = _buttonMap[ButtonType::EXIT_BUTTON].getSprite();
    SDL_Rect exitButtonClip = 
    {
        _buttonMap[ButtonType::EXIT_BUTTON].getSize().w * exitButtonSprite,
        0,
        _buttonMap[ButtonType::EXIT_BUTTON].getSize().w,
        _buttonMap[ButtonType::EXIT_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::EXIT_BUTTON].draw(p_renderer, _buttonMap[ButtonType::EXIT_BUTTON].getPosition(), 0.0, &exitButtonClip);
}
