#pragma once
#include "GameHeader.h"
#include "GameObject.h"
#include "Spaceship.h"

#define TRACKER_VELOCITY 15
#define TRACKER_ACCELERATION 1
#define TRACKER_WIDTH 30
#define TRACKER_HEIGHT 30

class Tracker : public GameObject
{
public:
    static constexpr int STATE_DISABLE = -1;
    static constexpr int STATE_ENABLE_DEFAULT = 0;

    Tracker() : GameObject(ObjectType::TRACKER, {TRACKER_WIDTH, TRACKER_HEIGHT})
    {
        key = {0, 0, 0, 0};
        velocityVector = {0, 0};
        acceleration = 0;

        p_tracking = nullptr;
        p_previousTracking = nullptr;
        
        for (int i = 0; i < Side::TOTAL_SIDES; i++)
        {
            collision[i] = false;
        }
    }
    virtual ~Tracker() = default;

    Spaceship *getTracking() const;
    void setTrancking(Spaceship *_p_spaceship);

    void setKey(const ShootingControl &_key);

    bool checkCollision_inside(const GameObject *_p_other);
    bool checkCollision_outside(const GameObject *_p_other);
    void handleCollision(const ObjectType &_type, Spaceship *_p_spaceship = nullptr);
    void move(const unsigned char *_p_keyState, const std::vector<Spaceship *> &_p_spaceship);

    void reset(const std::vector<Spaceship *> &_p_spaceship);

private:
    void findTarget(const std::vector<Spaceship *> &_p_spaceship);

    ShootingControl key;
    Coordinate velocityVector;
    int acceleration;
    
    Spaceship *p_tracking;
    Spaceship *p_previousTracking;

    bool collision[Side::TOTAL_SIDES];
};