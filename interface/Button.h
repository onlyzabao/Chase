#pragma once
#include "Texture.h"

class Button
{
public:
    static constexpr int SPRITE_DEFAULT = 0;
    static constexpr int SPRITE_MOUSEOVER = 1;

    Button()
    {
        position = {0, 0};
        size = {0, 0};
        sprite = SPRITE_DEFAULT;
        clicked = false;
    }
    ~Button() = default;

    Coordinate getPosition() const;
    Size getSize() const;
    int getSprite() const;
    bool isClicked() const;

    void setPosition(const Coordinate &_position);
    void setSize(const Size &_size);
    void setSprite(const int &_sprite);

    void handleEvent(SDL_Event *_p_event);

private:
    Coordinate position;
    Size size;
    int sprite;
    bool clicked;
};