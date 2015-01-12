#pragma once
#include "glimac/SDLWindowManager.hpp"

class Player;
class MovementAbstract{
    protected:
        Player& m_player;
    public:
        MovementAbstract(Player& player);
        virtual void updatePositionPlayer(glimac::SDLWindowManager const& events) = 0;
        static const float METER_WALKED_PER_FRAME;
};
