#include "Rocket.h"

Coordinate Rocket::getVelocityVector() const
{
    return velocityVector;
}

void Rocket::updateState()
{
    static constexpr Coordinate startPosition[8] = 
    {
        {SCREEN_WIDTH / 4 - ROCKET_WIDTH / 2, SCREEN_HEIGHT * 3},
        {(SCREEN_WIDTH * 3) / 4 - ROCKET_WIDTH / 2, SCREEN_HEIGHT * 3},
        {SCREEN_WIDTH / 4 - ROCKET_WIDTH / 2, -SCREEN_HEIGHT * 2},
        {(SCREEN_WIDTH * 3) / 4 - ROCKET_WIDTH / 2, -SCREEN_HEIGHT * 2},
        {SCREEN_WIDTH * 2, SCREEN_HEIGHT / 4 - ROCKET_HEIGHT / 2},
        {SCREEN_WIDTH * 2, (SCREEN_HEIGHT * 3) / 4 - ROCKET_HEIGHT / 2},
        {-SCREEN_WIDTH, SCREEN_HEIGHT / 2 - ROCKET_HEIGHT / 2},
        {-SCREEN_WIDTH, (SCREEN_HEIGHT * 3) / 4 - ROCKET_HEIGHT / 2}
    };

    if (state == STATE_ENABLE_EXPLOSION)
    {
        livingTime.end = CLOCK_NOW();
        if (livingTime.calculateDuration() > ROCKET_EXPLOSION_TIME)
        {
            state = STATE_DISABLE;
            position = startPosition[rand() % 8];
        }
    }
    else
    {
        Coordinate topLeft = {0, 0};
        Coordinate bottomRight = {SCREEN_WIDTH, SCREEN_HEIGHT};

        if (position.y >= bottomRight.y || position.y + size.h <= topLeft.y || position.x >= bottomRight.x || position.x + size.w <= topLeft.x)
        {
            livingTime.end = CLOCK_NOW();
            if (livingTime.calculateDuration() > ROCKET_RESETING_TIME)
            {
                state = STATE_ENABLE_SIGN;
            }
        }
        else
        {
            state = STATE_ENABLE_DEFAULT;
        }
    }
}

bool Rocket::checkCollision_outside(const GameObject *_p_other) const
{
    if (state == STATE_ENABLE_DEFAULT)
    {
        Coordinate topLeft = _p_other->getPosition();
        Coordinate bottomRight = topLeft + _p_other->getSize();

        if (position.y >= bottomRight.y)
        {
            return false;
        }
        if (position.y + size.h <= topLeft.y)
        {
            return false;
        }
        if (position.x >= bottomRight.x)
        {
            return false;
        }
        if (position.x + size.w <= topLeft.x)
        {
            return false;
        }
        return true;
    }
    return false;
}

void Rocket::findTarget(const Tracker *_p_tracker)
{
    p_previousChasing = p_chasing;
    if (_p_tracker->getState() == Tracker::STATE_DISABLE)
    {
        p_chasing = _p_tracker->getTracking();
    }
    else
    {
        p_chasing = nullptr;
    }
    if (p_chasing == nullptr)
    {
        p_chasing = p_previousChasing;
    }
}

void Rocket::move(const Tracker *_p_tracker)
{
    if (state != STATE_ENABLE_EXPLOSION)
    {
        findTarget(_p_tracker);
        if (p_chasing != nullptr)
        {
            Coordinate target = p_chasing->getPosition() + p_chasing->getSize() / 2;
            Coordinate radiusVector =  target - position;

            angle = radiusVector.calculateAngle() - velocityVector.calculateAngle();
            if (fabs(angle) > M_PI)
            {
                double tmp = (M_PI * 2 - fabs(angle));
                if (angle > 0)
                {
                    angle = -tmp;
                }
                if (angle < 0)
                {
                    angle = tmp;
                }
            }

            angle = velocityVector.calculateAngle() + angle / 2;

            if (angle > M_PI)
            {
                angle -= M_PI * 2;
            }
            if (angle < -M_PI)
            {
                angle += M_PI * 2;
            }

            velocityVector.x = velocityValue * cos(angle);
            velocityVector.y = velocityValue * sin(angle);

            position.x += velocityVector.x;
            position.y += velocityVector.y;

            livingTime.end = CLOCK_NOW();
            if (livingTime.calculateDuration() > ROCKET_LIVING_TIME)
            {
                if (livingTime.calculateDuration() > ROCKET_LIVING_TIME + ROCKET_RESETING_TIME)
                {
                    velocityValue += ROCKET_ACCELERATION;
                }
                else
                {
                    velocityValue = ROCKET_VELOCITY / 2;
                }
            }
        }
    }
}

void Rocket::reset()
{
    p_chasing = nullptr;
    p_previousChasing = nullptr;
    velocityValue = ROCKET_VELOCITY;
    state = STATE_ENABLE_EXPLOSION;
    velocityVector = {0, 0};
    livingTime.begin = CLOCK_NOW();
}

