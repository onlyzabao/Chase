#include "GameEngine.h"


void GameEngine::init(const std::vector<Coordinate> &_startPosition, const std::vector<MovementControl> &_movementKey, const ShootingControl &_shootingKey)
{
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < playerNumber; i++)
    {
        p_spaceship[i] = new Spaceship(static_cast<Player>(i));
        p_spaceship[i]->setKey(_movementKey[i]);
        p_spaceship[i]->setPosition(_startPosition[i]);
    }

    p_tracker = new Tracker;
    p_tracker->setKey(_shootingKey);
    p_tracker->setPosition(_startPosition[rand() % playerNumber] - p_tracker->getSize());

    p_rocket = new Rocket;
    
    p_barrier = new Barrier;
}

void GameEngine::free()
{
    for (auto spaceship : p_spaceship)
    {
        delete spaceship;
        spaceship = nullptr;
    }

    delete p_tracker;
    p_tracker = nullptr;

    delete p_rocket;
    p_rocket = nullptr;

    delete p_barrier;
    p_barrier = nullptr;
}

void GameEngine::handleMovement(const GameUI *_p_gameUI)
{
    const Uint8 *_p_keyState = _p_gameUI->getKeyState();

    for (auto spaceship : p_spaceship)
    {
        spaceship->move(_p_keyState);
    }
    
    p_tracker->move(_p_keyState, p_spaceship);

    p_rocket->move(p_tracker);
    p_rocket->updateState();

    if (p_tracker->getTracking() != nullptr && p_tracker->getState() == Tracker::STATE_DISABLE)
    {
        p_barrier->updateState((p_tracker->getTracking())->getDriver());
    }
}

void GameEngine::handleCollision(const GameUI *_p_gameUI)
{
    if (p_tracker->checkCollision_inside(p_barrier))
    {
        p_tracker->handleCollision(ObjectType::BARRIER);
    }

    for (int i = 0; i < playerNumber; i++)
    {
        if (p_rocket->checkCollision_outside(p_spaceship[i]))
        {
            explosionPosition = p_spaceship[i]->getPosition() + p_spaceship[i]->getSize() / 2;
            _p_gameUI->playSound(Sound::EXPLOSION_SOUND);
            
            if (p_spaceship[i]->getFate() == 1)
            {
                playerNumber--;
                delete p_spaceship[i];
                p_spaceship.erase(p_spaceship.begin() + i);
            }
            else
            {
                p_spaceship[i]->reset();
            }

            p_rocket->reset();
            p_tracker->reset(p_spaceship);
            break;
        }

        if (p_tracker->checkCollision_outside(p_spaceship[i]))
        {
            _p_gameUI->playSound(Sound::TRACKED_SOUND);
            p_tracker->handleCollision(ObjectType::SPACESHIP, p_spaceship[i]);
        }

        if (p_spaceship[i]->checkCollision_inside(p_barrier))
        {
            p_spaceship[i]->handleCollision(ObjectType::BARRIER);
        }

        for (int j = i + 1; j < playerNumber; j++)
        {
            if (p_spaceship[i]->checkCollision_outside(p_spaceship[j]))
            {
                p_spaceship[i]->handleCollision(ObjectType::SPACESHIP, p_spaceship[j]);
            }

            if (p_spaceship[j]->checkCollision_outside(p_spaceship[i]))
            {
                p_spaceship[j]->handleCollision(ObjectType::SPACESHIP, p_spaceship[i]);
            }
        }
    }
}

void GameEngine::draw(const GameUI *_p_gameUI)
{
    std::vector<GameObject *> map(TOTAL_DEFAULT_OBJECTS, nullptr);
    map[ObjectType::BARRIER] = p_barrier;
    if (p_rocket->getState() != Rocket::STATE_DISABLE)
    {
        map[ObjectType::ROCKET] = p_rocket;
    }
    if (p_tracker->getState() != Tracker::STATE_DISABLE)
    {
        map[ObjectType::TRACKER] = p_tracker;
    }
    for (int i = 0; i < playerNumber; i++)
    {
        map.push_back(p_spaceship[i]);
    }

    _p_gameUI->clear();
    _p_gameUI->drawBackground();
    _p_gameUI->drawPlayground(map);
    for (int i = 0; i < playerNumber; i++)
    {
        _p_gameUI->drawFate(p_spaceship[i]->getDriver(), p_spaceship[i]->getFate());
    }
    _p_gameUI->present();
}

void GameEngine::updateStatus(Status &_status) const
{
    if (playerNumber == 1)
    {
        _status = Status::END_STATUS;
    }
}

Player GameEngine::getWinner() const
{
    if (playerNumber == 1)
    {
        return p_spaceship.front()->getDriver();
    }
    return Player::NONE_PLAYER;
}