#pragma once
#include "GameHeader.h"
#include "GameObject.h"

#define BARRIER_WIDTH 1400
#define BARRIER_HEIGHT 700

class Barrier : public GameObject
{
public:
    static constexpr int STATE_DISABLE = -1;
    static constexpr int STATE_ENABLE_PLAYER_1 = 0;
    static constexpr int STATE_ENABLE_PLAYER_2 = 1;
    static constexpr int STATE_ENABLE_PLAYER_3 = 2;
    static constexpr int STATE_ENABLE_PLAYER_4 = 3;

    Barrier() : GameObject(ObjectType::BARRIER, {BARRIER_WIDTH, BARRIER_HEIGHT}, {(SCREEN_WIDTH - BARRIER_WIDTH) / 2, (SCREEN_HEIGHT - BARRIER_HEIGHT) / 2}) {}
    virtual ~Barrier() = default;

    void updateState(const Player &_driver);
};