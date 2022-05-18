#pragma once
#include "GameHeader.h"

class GameObject
{
public:
    GameObject(ObjectType _type= ObjectType::NONE_TYPE, Size _size = {0, 0}, Coordinate _position = {0, 0}, double _angle = 0.0, int _state = 0)
    {
        type = _type;
        position = _position;
        size = _size;
        angle = _angle;
        state = _state;
    }
    virtual ~GameObject() = default;
    
    ObjectType getType() const;
    Coordinate getPosition() const;
    Size getSize() const;
    double getAngle() const;
    int getState() const;

    void setType(const ObjectType&_type);
    void setPosition(const Coordinate &_position);
    void setSize(const Size &_size);

    virtual Player getDriver() const;
    
protected:
    ObjectType type;
    Coordinate position;
    Size size;
    double angle;
    int state;
};