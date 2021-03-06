#include "Movement.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <iostream>
#include "Game.hpp"

Movement::Movement(Player& player):MovementAbstract(player),m_jumpCurrentFrame(0), m_isJumping(false),
    m_collisionModule(player, MovementAbstract::METER_WALKED_PER_FRAME*4){ //raise distance compare collision: avoid display bugs
    m_jumpVector = glm::vec3(0,MovementAbstract::METER_WALKED_PER_FRAME,0);
    m_jumpFrameDuration = 1.2 / MovementAbstract::METER_WALKED_PER_FRAME; //1.2 metter in Y
    m_lockCtrlKey = false;
}

void Movement::jump(){

    if(!m_collisionModule.isImpactUp() && m_isJumping && m_jumpCurrentFrame < m_jumpFrameDuration /*&& m_falling_inertie < m_jumpVector.y*/){
        m_player.movePosition(m_jumpVector);
        m_player.camera().movePosition(m_jumpVector);
        ++m_jumpCurrentFrame;
    }
    else{
        m_isJumping = false;
        m_jumpCurrentFrame = 0;
       // m_falling_inertie -= m_jumpVector.y;
    }
}

void Movement::updatePositionPlayer(const glimac::SDLWindowManager &events){

    glm::ivec2 mouseCurrenPosition =  events.getMouseMotionRelative();
    m_player.camera().rotateLeft(-(mouseCurrenPosition.x)/3.);
    m_player.camera().rotateUp(-( mouseCurrenPosition.y)/3.);

    m_collisionModule.setPositionRoundPlayer(m_player.position());
    if(m_isJumping)
        this->jump();


    if(events.isKeyPressed(SDLK_LCTRL) && !m_lockCtrlKey){
        m_lockCtrlKey = true;
        m_lookAtSave = m_player.camera().frontVectorYconstant()*3.f;
        m_player.camera().movePosition(m_lookAtSave);
        m_player.camera().setPhi(m_player.camera().phi() + glm::pi<float>());
    }

    if(!events.isKeyPressed(SDLK_LCTRL) && m_lockCtrlKey){
        m_lockCtrlKey = false;
        m_player.camera().movePosition(-m_lookAtSave);
        m_player.camera().setPhi(m_player.camera().phi() + glm::pi<float>());
    }

    glm::vec3 vectorMovement = glm::vec3(0,0,0);
    if(events.isKeyPressed(SDLK_z)){
        vectorMovement += m_player.camera().frontVectorYconstant();
    }
    if(events.isKeyPressed(SDLK_s)){
        vectorMovement -= m_player.camera().frontVectorYconstant();
    }
    if(events.isKeyPressed(SDLK_q)){
        vectorMovement += m_player.camera().leftVector();
    }
    if(events.isKeyPressed(SDLK_d)){
        vectorMovement -= m_player.camera().leftVector();
    }
    if(events.isKeyPressed(SDLK_SPACE) && !m_isJumping && !m_collisionModule.isFalling()){
        m_isJumping = true;
    }

    if(vectorMovement != glm::vec3(0,0,0)){
        vectorMovement = glm::normalize(vectorMovement);
        vectorMovement *= MovementAbstract::METER_WALKED_PER_FRAME;

        if((vectorMovement.z >0 && m_collisionModule.isImpactFront()) || vectorMovement.z <0 && m_collisionModule.isImpactBack())
            vectorMovement.z = 0;
        if((vectorMovement.x >0 && m_collisionModule.isImpactLeft()) || vectorMovement.x <0 && m_collisionModule.isImpactRight())
            vectorMovement.x = 0;

        m_player.movePosition(vectorMovement);
        m_player.camera().movePosition(vectorMovement);
    }
    if(!m_isJumping){
        m_collisionModule.setPositionRoundPlayer(m_player.position());
        //m_falling_inertie += 0.091/Game::FRAME_PER_SECOND;
        if(m_collisionModule.isFalling()){
            glm::vec3 vectorMoveY = glm::vec3(0,-MovementAbstract::METER_WALKED_PER_FRAME,0);
            m_player.movePosition(vectorMoveY);
            m_player.camera().movePosition(vectorMoveY);
        }
    }
}
