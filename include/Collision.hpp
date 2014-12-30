#pragma once
#include <glimac/glm.hpp>

class Game;
class Player;
class Collision{
    private:
        Player& m_player;                //access to voxels via player
        float m_stepMoveAnticipated;     //distance in any directions
        glm::vec3 m_positionRoundPlayer; //avoid multiple round useless in impact compute

    public:
        Collision(Player& player, float stepMoveAnticipated=0.07); //0.07 => distance walked in meter for 1 frame (60 fps)
        glm::vec3 positionRoundPlayer() const;
        float stepMoveAnticipated() const;

        void setStepMoveAnticipated(float anticipatedMove);
        void setPositionRoundPlayer(glm::vec3 const& position);

        bool isCubePresent(int x, int y, int z) const;

        bool isImpactFront() const;
        bool isImpactBack() const;
        bool isImpactLeft() const;
        bool isImpactRight() const;
        bool isImpactUp() const;
        bool isFalling() const;
};
