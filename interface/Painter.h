#pragma once
#include "Texture.h"
#include "Button.h"
#include "../core/GameObject.h"

#define PLAYER_1_COLOR {255, 65, 65, 255}
#define PLAYER_2_COLOR {65, 214, 255, 255}
#define PLAYER_3_COLOR {40, 195, 4, 255}
#define PLAYER_4_COLOR {183, 78, 255, 255}
#define MAIN_COLOR {250, 193, 0, 255}

class Painter
{
public:
    static constexpr int TOTAL_DEFAULT_PLAYGROUND_OBJECTS = 3;
    static constexpr int TITLE_TEXT_SIZE = 200;
    static constexpr int WINNER_TEXT_SIZE = 150;

    Painter()
    {
        p_renderer = nullptr;
        p_titleTextFont = nullptr;
        p_winnerTextFont = nullptr;

        backgroundTexture = Texture();
        menuTitleTexture = Texture();

        fateTexture = std::vector<Texture>(Player::TOTAL_PLAYERS, Texture());
        playgroundTexture = std::vector<Texture>(ObjectType::TOTAL_TYPES + Player::TOTAL_PLAYERS - 1, Texture());

        miniMenuTitleTexture = std::vector<Texture>(Player::TOTAL_PLAYERS, Texture());

        buttonTexture = std::vector<Texture>(ButtonType::TOTAL_BUTTONS, Texture());
    }
    ~Painter();

    bool init(SDL_Window *_p_window);
    bool loadTexture();
    void free();

    void drawBackground() const;

    void drawFate(const Player &_driver, const int &_fate) const;
    void drawPlayground(const std::vector<GameObject *> &_map) const;

    void drawMiniMenu(const Player &_winner, const std::vector<Button> &_buttonMap) const;
    void drawMainMenu(const std::vector<Button> &_buttonMap) const;

protected:
    SDL_Renderer *p_renderer;
    TTF_Font *p_titleTextFont;
    TTF_Font *p_winnerTextFont;

    Texture backgroundTexture;
    Texture menuTitleTexture;

    std::vector<Texture> playgroundTexture;
    std::vector<Texture> fateTexture;

    std::vector<Texture> miniMenuTitleTexture;

    std::vector<Texture> buttonTexture;
};
