#pragma once
#include "GameHeader.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "Tracker.h"

#define ROCKET_VELOCITY 5
#define ROCKET_ACCELERATION 1
#define ROCKET_WIDTH 50
#define ROCKET_HEIGHT 50

class Rocket : public GameObject
{
public:
    static constexpr double ROCKET_LIVING_TIME = 15.0;
    static constexpr double ROCKET_RESETING_TIME = 1.0;
    static constexpr double ROCKET_EXPLOSION_TIME = 0.5;

    static constexpr int STATE_DISABLE = -1;
    static constexpr int STATE_ENABLE_DEFAULT = 0;
    static constexpr int STATE_ENABLE_SIGN = 1;
    static constexpr int STATE_ENABLE_EXPLOSION = 2;

    Rocket() : GameObject(ObjectType::ROCKET, {ROCKET_WIDTH, ROCKET_HEIGHT}, {SCREEN_WIDTH / 2 - ROCKET_WIDTH / 2, SCREEN_HEIGHT * 4})
    {
        velocityVector = {0 , ROCKET_VELOCITY};
        velocityValue = ROCKET_VELOCITY;

        p_chasing = nullptr;
        p_previousChasing = nullptr;

        livingTime = {CLOCK_NOW(), CLOCK_NOW()};
    }
    virtual ~Rocket() = default;

    Coordinate getVelocityVector() const;

    void updateState();
    bool checkCollision_outside(const GameObject *_p_other) const;
    void move(const Tracker *_p_tracker);

    void reset();

private:
    void findTarget(const Tracker *_p_tracker);

    Coordinate velocityVector;
    int velocityValue;
    
    Spaceship *p_chasing;
    Spaceship *p_previousChasing;

    Time livingTime;
};