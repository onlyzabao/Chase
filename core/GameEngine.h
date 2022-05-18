#pragma once
#include "GameHeader.h"
#include "../interface/GameUI.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "Rocket.h"
#include "Tracker.h"
#include "Barrier.h"

class GameEngine
{
public:
    static constexpr int TOTAL_DEFAULT_OBJECTS = 3;

    GameEngine(const int &_playerNumber)
    {
        playerNumber = _playerNumber;

        explosionPosition = {-SCREEN_WIDTH, -SCREEN_HEIGHT}; //TODO: Remove this

        p_spaceship = std::vector<Spaceship *>(_playerNumber, nullptr);
        p_tracker = nullptr;
        p_rocket = nullptr;
        p_barrier = nullptr;
    }
    ~GameEngine() = default;

    void init(const std::vector<Coordinate> &_startPosition, const std::vector<MovementControl> &_movementKey, const ShootingControl &_shootingKey);
    void free();

    Player getWinner() const;
    void updateStatus(Status &_status) const;

    void handleMovement(const GameUI *_p_gameUI);
    void handleCollision(const GameUI *_p_gameUI);
    void draw(const GameUI *_p_gameUI);

private:
    int playerNumber;
    
    Coordinate explosionPosition;

    std::vector<Spaceship *> p_spaceship;
    Tracker *p_tracker;
    Rocket *p_rocket;
    Barrier *p_barrier;
};
