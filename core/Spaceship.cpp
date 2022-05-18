#include "Spaceship.h"

Player Spaceship::getDriver() const
{
    return driver;
}

Coordinate Spaceship::getVelocityVector() const
{
    return velocityVector;
}

int Spaceship::getFate() const
{
    return fate;
}

void Spaceship::setKey(const MovementControl &_key)
{
    key = _key;
}

bool Spaceship::checkCollision_inside(const GameObject *_p_other)
{
    Coordinate topLeft = _p_other->getPosition();
    Coordinate bottomRight = topLeft + _p_other->getSize();

    collision[Side::TOP] = position.y < topLeft.y;
    collision[Side::BOTTOM] = position.y + size.h > bottomRight.y;
    collision[Side::LEFT] = position.x < topLeft.x;
    collision[Side::RIGHT] = position.x + size.w > bottomRight.x;

    return (collision[Side::TOP] || collision[Side::BOTTOM] || collision[Side::LEFT] || collision[Side::RIGHT]);
}

bool Spaceship::checkCollision_outside(const GameObject *_p_other)
{
    Coordinate topLeft = _p_other->getPosition();
    Coordinate bottomRight = topLeft + _p_other->getSize();

    bool topIn = (topLeft.y <= position.y) && (position.y <= bottomRight.y);
    bool bottomIn = (topLeft.y <= position.y + size.h) && (position.y + size.h <= bottomRight.y);
    bool leftIn = (topLeft.x <= position.x) && (position.x <= bottomRight.x);
    bool rightIn = (topLeft.x <= position.x + size.w) && (position.x + size.w <= bottomRight.x);

    collision[Side::TOP] = topIn && (leftIn || rightIn);
    collision[Side::BOTTOM] = bottomIn && (leftIn || rightIn);
    collision[Side::LEFT] = leftIn && (topIn || bottomIn);
    collision[Side::RIGHT] = rightIn && (topIn || bottomIn);

    return (collision[Side::TOP] || collision[Side::BOTTOM] || collision[Side::LEFT] || collision[Side::RIGHT]);
}

void Spaceship::move(const unsigned char *_p_keyState)
{
    resetingTime.end = CLOCK_NOW();
    if (resetingTime.calculateDuration() > SPACESHIP_RESETING_TIME || state != STATE_ENABLE_RESETING)
    {
        state = STATE_ENABLE_DEFAULT;

        velocityVector.x = (_p_keyState[key.right] - _p_keyState[key.left]) * velocityValue;
        velocityVector.y = (_p_keyState[key.down] - _p_keyState[key.up]) * velocityValue;
        
        if (velocityVector.x == velocityVector.y || velocityVector.x == -velocityVector.y)
        {
            velocityVector.x = (velocityVector.x * 4) / 5;
            velocityVector.y = (velocityVector.y * 3) / 5;
        }

        velocityVector.calculateAngle(angle);
        
        position.x += velocityVector.x;
        position.y += velocityVector.y;
    }
}

void Spaceship::handleCollision(const ObjectType &_type, Spaceship *_p_spaceship)
{
    switch (_type)
    {
        case ObjectType::SPACESHIP:
            position.x += (collision[Side::LEFT] - collision[Side::RIGHT]) * SPACESHIP_VELOCITY;
            position.y += (collision[Side::TOP] - collision[Side::BOTTOM]) * SPACESHIP_VELOCITY;
            if (_p_spaceship != nullptr)
            {
                Coordinate otherPosition = _p_spaceship->getPosition();
                otherPosition.x -= (collision[Side::LEFT] - collision[Side::RIGHT]) * SPACESHIP_VELOCITY;
                otherPosition.y -= (collision[Side::TOP] - collision[Side::BOTTOM]) * SPACESHIP_VELOCITY;
                _p_spaceship->setPosition(otherPosition);
            }
            break;

        case ObjectType::BARRIER:
            if (collision[Side::LEFT] || collision[Side::RIGHT])
            {
                if (velocityVector.x != 0)
                {
                    position.x -= velocityVector.x;
                }
                else
                {
                    position.x += (collision[Side::LEFT] - collision[Side::RIGHT]) * SPACESHIP_VELOCITY * 2;
                }
            }
            if (collision[Side::TOP] || collision[Side::BOTTOM])
            {
                if (velocityVector.y != 0)
                {
                    position.y -= velocityVector.y; 
                }
                else
                {
                    position.y += (collision[Side::TOP] - collision[Side::BOTTOM]) * SPACESHIP_VELOCITY * 2;
                }
            }
            break;
    }
}

void Spaceship::reset()
{
    static constexpr Coordinate startPosition[Player::TOTAL_PLAYERS] = 
    {
        {SCREEN_WIDTH / 4 - SPACESHIP_WIDTH / 2, (SCREEN_HEIGHT * 3) / 4 - SPACESHIP_HEIGHT / 2},
        {(SCREEN_WIDTH * 3) / 4 - SPACESHIP_WIDTH / 2, (SCREEN_HEIGHT * 3) / 4 - SPACESHIP_HEIGHT / 2},
        {SCREEN_WIDTH / 4 - SPACESHIP_WIDTH / 2, SCREEN_HEIGHT / 4 - SPACESHIP_HEIGHT / 2},
        {(SCREEN_WIDTH * 3) / 4 - SPACESHIP_WIDTH / 2, SCREEN_HEIGHT / 4 - SPACESHIP_HEIGHT / 2},
    };

    fate--;
    position = startPosition[driver];
    angle = -M_PI / 2;
    velocityVector = {0, -velocityValue};
    state = STATE_ENABLE_RESETING;
    resetingTime.begin = CLOCK_NOW();
}

