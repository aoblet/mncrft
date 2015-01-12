#pragma once
#include <string>
#include "CameraFirstPerson.hpp"
#include "glimac/glm.hpp"
#include "Movement.hpp"
#include "glimac/SDLWindowManager.hpp"
#include "GameInteraction.hpp"
#include "CubeData.hpp"

class Game;
class Player{
    public:
        std::string m_name;
        int m_life;
        Movement m_movementModule;
        glm::vec3 m_position;
        GameInteraction m_gameInteraction;
        CubeType m_current_CubeType;

    public:
        Player(Game * game=nullptr, glm::vec3 const& position=glm::vec3(0,0,0), std::string const& name="Nooby 3000", int life=10);
        CameraFirstPerson m_camera;

        glm::vec3 position() const;
        CameraFirstPerson &camera();
        CameraFirstPerson camera() const;
        Game* game();
        int life() const;
        std::string name() const;
        GameInteraction& gameInteraction();
        GameInteraction gameInteraction() const;
        CubeType currentCubeType() const;

        void movePosition(glm::vec3 const& vectorMovement);
        void setPosition(glm::vec3 const& position);
        void setName(std::string const& name);
        void setGame(Game* game);
        void handleMove(glimac::SDLWindowManager const& events);
        void setCurrentCubeType(CubeType const& type) ;
};
