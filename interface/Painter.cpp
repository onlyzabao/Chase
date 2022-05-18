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
    if (!startMenuTitleTexture.loadFromRenderedText(p_renderer, p_titleTextFont, "GAME MODE", MAIN_COLOR))
    {
        std::cout << "Unable to load start menu title texture." << std::endl;
        return false;
    }

    // Playground texture
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
    if (!miniMenuTexture[Player::PLAYER_1].loadFromRenderedText(p_renderer, p_winnerTextFont, "PLAYER 1 WIN!", PLAYER_1_COLOR))
    {
        std::cout << "Unable to load winner texture." << std::endl;
        return false;
    }
    if (!miniMenuTexture[Player::PLAYER_2].loadFromRenderedText(p_renderer, p_winnerTextFont, "PLAYER 2 WIN!", PLAYER_2_COLOR))
    {
        std::cout << "Unable to load winner texture." << std::endl;
        return false;
    }
    if (!miniMenuTexture[Player::PLAYER_3].loadFromRenderedText(p_renderer, p_winnerTextFont, "PLAYER 3 WIN!", PLAYER_3_COLOR))
    {
        std::cout << "Unable to load winner texture." << std::endl;
        return false;
    }
    if (!miniMenuTexture[Player::PLAYER_4].loadFromRenderedText(p_renderer, p_winnerTextFont, "PLAYER 4 WIN!", PLAYER_4_COLOR))
    {
        std::cout << "Unable to load winner texture." << std::endl;
        return false;
    }
    if (!miniMenuTitleTexture.loadFromRenderedText(p_renderer, p_titleTextFont, "MINI MENU", MAIN_COLOR))
    {
        std::cout << "Unable to load mini menu title texture." << std::endl;
        return false;
    }

    // Guide texture
    if (!guideTexture[Player::PLAYER_1].loadFromFile(p_renderer, "./asset/png/menu/player_1.png"))
    {
        std::cout << "Unable to load guide texture." << std::endl;
        return false;
    }
    if (!guideTexture[Player::PLAYER_2].loadFromFile(p_renderer, "./asset/png/menu/player_2.png"))
    {
        std::cout << "Unable to load guide texture." << std::endl;
        return false;
    }
    if (!guideTexture[Player::PLAYER_3].loadFromFile(p_renderer, "./asset/png/menu/player_3.png"))
    {
        std::cout << "Unable to load guide texture." << std::endl;
        return false;
    }
    if (!guideTexture[Player::PLAYER_4].loadFromFile(p_renderer, "./asset/png/menu/player_4.png"))
    {
        std::cout << "Unable to load guide texture." << std::endl;
        return false;
    }

    // Button texture
    if (!buttonTexture[ButtonType::START_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/start_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }
    if (!buttonTexture[ButtonType::RESTART_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/restart_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }
    if (!buttonTexture[ButtonType::RESUME_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/resume_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }
    if (!buttonTexture[ButtonType::GUIDE_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/guide_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }
    if (!buttonTexture[ButtonType::EXIT_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/exit_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }
    if (!buttonTexture[ButtonType::TWO_PLAYER_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/two_player_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }if (!buttonTexture[ButtonType::THREE_PLAYER_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/three_player_button.png"))
    {
        std::cout << "Unable to load button texture." << std::endl;
        return false;
    }
    if (!buttonTexture[ButtonType::FOUR_PLAYER_BUTTON].loadFromFile(p_renderer, "./asset/png/menu/FOUR_player_button.png"))
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
    miniMenuTitleTexture.free();
    startMenuTitleTexture.free();

    for (auto texture : fateTexture)
    {
        texture.free();
    }

    for (auto texture : playgroundTexture)
    {
        texture.free();
    }

    for (auto texture : guideTexture)
    {
        texture.free();
    }

    for (auto texture : miniMenuTexture)
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
    if (_winner == Player::NONE_PLAYER)
    {
        Coordinate titlePosition = {(SCREEN_WIDTH - miniMenuTitleTexture.getSize().w) / 2, (SCREEN_HEIGHT - miniMenuTitleTexture.getSize().h) / 6};
        miniMenuTitleTexture.draw(p_renderer, titlePosition);
    }
    else
    {
        Coordinate titlePosition = {(SCREEN_WIDTH - miniMenuTexture[_winner].getSize().w) / 2, (SCREEN_HEIGHT - miniMenuTexture[_winner].getSize().h) / 4};
        miniMenuTexture[_winner].draw(p_renderer, titlePosition);
    }

    int restartButtonSprite = _buttonMap[ButtonType::RESTART_BUTTON].getSprite();
    SDL_Rect restartButtonClip = 
    {
        _buttonMap[ButtonType::RESTART_BUTTON].getSize().w * restartButtonSprite,
        0,
        _buttonMap[ButtonType::RESTART_BUTTON].getSize().w,
        _buttonMap[ButtonType::RESTART_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::RESTART_BUTTON].draw(p_renderer, _buttonMap[ButtonType::RESTART_BUTTON].getPosition(), 0.0, &restartButtonClip);

    int resumeButtonSprite = _buttonMap[ButtonType::RESUME_BUTTON].getSprite();
    SDL_Rect resumeButtonClip = 
    {
        _buttonMap[ButtonType::RESUME_BUTTON].getSize().w * resumeButtonSprite,
        0,
        _buttonMap[ButtonType::RESUME_BUTTON].getSize().w,
        _buttonMap[ButtonType::RESUME_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::RESUME_BUTTON].draw(p_renderer, _buttonMap[ButtonType::RESUME_BUTTON].getPosition(), 0.0, &resumeButtonClip);

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

    int guideButtonSprite = _buttonMap[ButtonType::GUIDE_BUTTON].getSprite();
    SDL_Rect guideButtonClip = 
    {
        _buttonMap[ButtonType::GUIDE_BUTTON].getSize().w * guideButtonSprite,
        0,
        _buttonMap[ButtonType::GUIDE_BUTTON].getSize().w,
        _buttonMap[ButtonType::GUIDE_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::GUIDE_BUTTON].draw(p_renderer, _buttonMap[ButtonType::GUIDE_BUTTON].getPosition(), 0.0, &guideButtonClip);

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

void Painter::drawGuideMenu(const std::vector<Button> &_buttonMap) const
{
    guideTexture[Player::PLAYER_1].draw(p_renderer, {100, 100});
    guideTexture[Player::PLAYER_2].draw(p_renderer, {850, 100});
    guideTexture[Player::PLAYER_3].draw(p_renderer, {100, 450});
    guideTexture[Player::PLAYER_4].draw(p_renderer, {850, 450});

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

void Painter::drawStartMenu(const std::vector<Button> &_buttonMap) const
{
    static Coordinate titlePosition = {(SCREEN_WIDTH - startMenuTitleTexture.getSize().w) / 2, (SCREEN_HEIGHT - startMenuTitleTexture.getSize().h) / 8};
    startMenuTitleTexture.draw(p_renderer, titlePosition);

    int twoPlayerButtonSprite = _buttonMap[ButtonType::TWO_PLAYER_BUTTON].getSprite();
    SDL_Rect twoPlayerButtonClip = 
    {
        _buttonMap[ButtonType::TWO_PLAYER_BUTTON].getSize().w * twoPlayerButtonSprite,
        0,
        _buttonMap[ButtonType::TWO_PLAYER_BUTTON].getSize().w,
        _buttonMap[ButtonType::TWO_PLAYER_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::TWO_PLAYER_BUTTON].draw(p_renderer, _buttonMap[ButtonType::TWO_PLAYER_BUTTON].getPosition(), 0.0, &twoPlayerButtonClip);

    int threePlayerButtonSprite = _buttonMap[ButtonType::THREE_PLAYER_BUTTON].getSprite();
    SDL_Rect threePlayerButtonClip = 
    {
        _buttonMap[ButtonType::THREE_PLAYER_BUTTON].getSize().w * threePlayerButtonSprite,
        0,
        _buttonMap[ButtonType::THREE_PLAYER_BUTTON].getSize().w,
        _buttonMap[ButtonType::THREE_PLAYER_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::THREE_PLAYER_BUTTON].draw(p_renderer, _buttonMap[ButtonType::THREE_PLAYER_BUTTON].getPosition(), 0.0, &threePlayerButtonClip);

    int fourPlayerButtonSprite = _buttonMap[ButtonType::FOUR_PLAYER_BUTTON].getSprite();
    SDL_Rect fourPlayerButtonClip = 
    {
        _buttonMap[ButtonType::FOUR_PLAYER_BUTTON].getSize().w * fourPlayerButtonSprite,
        0,
        _buttonMap[ButtonType::FOUR_PLAYER_BUTTON].getSize().w,
        _buttonMap[ButtonType::FOUR_PLAYER_BUTTON].getSize().h
    };
    buttonTexture[ButtonType::FOUR_PLAYER_BUTTON].draw(p_renderer, _buttonMap[ButtonType::FOUR_PLAYER_BUTTON].getPosition(), 0.0, &fourPlayerButtonClip);
}