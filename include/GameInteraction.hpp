#pragma once

#include <glimac/SDLWindowManager.hpp>
#include "CubeData.hpp"

class Player;
class GameInteraction{
    private:
        Player& m_player; //access position, game voxels
        int m_lockClickFrameDuration;
        int m_currentLockClickFrame;

    public:
        GameInteraction(Player& player);
        int distanceIntersectionCube(int distanceMax) const; //distance intersect from player position: -1 if not
        void addCube(glm::vec3 const& positionVoxel, CubeType const& type);
        void hitCube(glm::vec3 const& positionVoxel);
        void handleInteraction(glimac::SDLWindowManager const& events);
        void handleChoiceCubeType(SDL_Event const& event);
};
