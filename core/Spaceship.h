#pragma once
#include "GameHeader.h"
#include "GameObject.h"

#define SPACESHIP_VELOCITY 5
#define SPACESHIP_WIDTH 50
#define SPACESHIP_HEIGHT 50

class Spaceship : public GameObject
{
public:
    static constexpr int MAX_FATE = 3;
    static constexpr double SPACESHIP_RESETING_TIME = 1.5;
    
    static constexpr int STATE_DISABLE = -1;
    static constexpr int STATE_ENABLE_DEFAULT = 0;
    static constexpr int STATE_ENABLE_RESETING = 1;

    Spaceship(const Player &_driver) : GameObject(ObjectType::SPACESHIP, {SPACESHIP_WIDTH, SPACESHIP_HEIGHT}, {0, 0}, -M_PI / 2)
    {
        driver = _driver;
        fate = MAX_FATE;
        
        key = {0, 0, 0, 0};
        velocityVector= {0, 0};
        velocityValue = SPACESHIP_VELOCITY;
        for (int i = 0; i < Side::TOTAL_SIDES; i++)
        {
            collision[i] = false;
        }

        resetingTime = {CLOCK_NOW(), CLOCK_NOW()};
    }
    virtual ~Spaceship() = default;

    virtual Player getDriver() const override;
    Coordinate getVelocityVector() const;
    int getFate() const;

    void setKey(const MovementControl &_key);

    bool checkCollision_inside(const GameObject *_p_other);
    bool checkCollision_outside(const GameObject *_p_other);
    void handleCollision(const ObjectType &_type, Spaceship *_p_spaceship = nullptr);
    void move(const unsigned char *_p_keyState);

    void reset();

private:
    Player driver;
    int fate;
    
    MovementControl key;
    Coordinate velocityVector;
    int velocityValue;
    bool collision[Side::TOTAL_SIDES];

    Time resetingTime;
};