#include "Button.h"

Coordinate Button::getPosition() const
{
    return position;
}

Size Button::getSize() const
{
    return size;
}

int Button::getSprite() const
{
    return sprite;
}

bool Button::isClicked() const
{
    return clicked;
}

void Button::setPosition(const Coordinate &_position)
{
    position = _position;
}

void Button::setSize(const Size &_size)
{
    size = _size;
}

void Button::setSprite(const int &_sprite)
{
    sprite = _sprite;
}

void Button::handleEvent(SDL_Event *_p_event)
{
    Coordinate mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    
    bool inside = true;
    if (mousePosition.x < position.x || mousePosition.x > position.x + size.w || mousePosition.y < position.y || mousePosition.y > position.y + size.h)
    {
        inside = false;
    }

    if (!inside)
    {
        sprite = SPRITE_DEFAULT;
        clicked = false;
    }
    else
    {
        sprite = SPRITE_MOUSEOVER;
        if (_p_event->type == SDL_MOUSEBUTTONDOWN)
        {
            clicked = true;
        }
        else
        {
            clicked = false;
        }
    }
}