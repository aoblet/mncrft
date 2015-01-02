#include "Movement.hpp"
#include "Collision.hpp"
#include "Player.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <iostream>

const float Movement::METER_WALKED_PER_FRAME = 0.07; //60fps 15kmh: jogging

Movement::Movement(Player& player): m_jumpCurrentFrame(0), m_isJumping(false), m_player(player),
                                    m_collisionModule(player, Movement::METER_WALKED_PER_FRAME*4){ //raise distance compare collision: avoid display bugs
    m_jumpVector = glm::vec3(0,Movement::METER_WALKED_PER_FRAME,0);
    m_jumpFrameDuration = 1.2 / Movement::METER_WALKED_PER_FRAME; //1.2 metter in Y
    m_lockCtrlKey = false;
}

void Movement::jump(){
    if(!m_collisionModule.isImpactUp() && m_isJumping && m_jumpCurrentFrame < m_jumpFrameDuration){
        m_player.movePosition(m_jumpVector);
        m_player.camera().movePosition(m_jumpVector);
        ++m_jumpCurrentFrame;
    }
    else{
        m_isJumping = false;
        m_jumpCurrentFrame = 0;
    }
}

void Movement::updatePositionPlayer(const glimac::SDLWindowManager &events){
    m_collisionModule.setPositionRoundPlayer(m_player.position());
    //std::cout << m_player.position() << std::endl;
    if(m_isJumping)
        this->jump();


    if(events.isKeyPressed(SDLK_LCTRL) && !m_lockCtrlKey){
        m_lockCtrlKey = true;
        m_lookAtSave = m_player.camera().frontVectorYconstant()*2.f;
        m_player.camera().movePosition(m_lookAtSave);
    }

    if(!events.isKeyPressed(SDLK_LCTRL) && m_lockCtrlKey){
        m_lockCtrlKey = false;
        m_player.camera().movePosition(-m_lookAtSave);
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
        vectorMovement *= Movement::METER_WALKED_PER_FRAME;

        if((vectorMovement.z >0 && m_collisionModule.isImpactFront()) || vectorMovement.z <0 && m_collisionModule.isImpactBack())
            vectorMovement.z = 0;
        if((vectorMovement.x >0 && m_collisionModule.isImpactLeft()) || vectorMovement.x <0 && m_collisionModule.isImpactRight())
            vectorMovement.x = 0;

        m_player.movePosition(vectorMovement);
        m_player.camera().movePosition(vectorMovement);
    }


    if(!m_isJumping){
        m_collisionModule.setPositionRoundPlayer(m_player.position());
        if(m_collisionModule.isFalling()){
            glm::vec3 vectorMoveY = glm::vec3(0,-Movement::METER_WALKED_PER_FRAME,0);
            m_player.movePosition(vectorMoveY);
            m_player.camera().movePosition(vectorMoveY);
        }
    }
}
