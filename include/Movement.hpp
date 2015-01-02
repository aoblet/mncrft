#pragma once
#include "Collision.hpp"
#include "glimac/SDLWindowManager.hpp"

class Player;
class Movement{
    private:
        Collision m_collisionModule;
        Player& m_player;
        int m_jumpCurrentFrame;
        int m_jumpFrameDuration;
        int m_isJumping;
        glm::vec3 m_jumpVector; //avoid multiple declaration inside jump method
        bool m_lockCtrlKey;
        glm::vec3 m_lookAtSave;
    public:
        Movement(Player& player);
        void updatePositionPlayer(glimac::SDLWindowManager const& events);
        void jump();
        static const float METER_WALKED_PER_FRAME;
};
