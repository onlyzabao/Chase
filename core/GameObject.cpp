#include "GameObject.h"

ObjectType GameObject::getType() const
{
    return type;
}

Coordinate GameObject::getPosition() const
{
    return position;
}

Size GameObject::getSize() const
{
    return size;
}

double GameObject::getAngle() const
{
    return angle;
}

int GameObject::getState() const
{
    return state;
}

Player GameObject::getDriver() const
{
    return Player::NONE_PLAYER;
}

void GameObject::setType(const ObjectType &_type)
{
    type = _type;
}

void GameObject::setPosition(const Coordinate &_position)
{
    position = _position;
}

void GameObject::setSize(const Size &_size)
{
    size = _size;
}