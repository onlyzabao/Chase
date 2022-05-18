#include "Barrier.h"

void Barrier::updateState(const Player &_driver)
{
    switch (_driver)
    {
    case Player::PLAYER_1:
        state = STATE_ENABLE_PLAYER_1;
        break;
    
    case Player::PLAYER_2:
        state = STATE_ENABLE_PLAYER_2;
        break;

    case Player::PLAYER_3:
        state = STATE_ENABLE_PLAYER_3;
        break;

    case Player::PLAYER_4:
        state = STATE_ENABLE_PLAYER_4;
        break;
    }
}

