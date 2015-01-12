#include "Collision.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <cmath>

Collision::Collision(Player& player, float stepMoveAnticipated):m_player(player),m_stepMoveAnticipated(stepMoveAnticipated){
    this->setPositionRoundPlayer(m_player.position());
}

glm::vec3 Collision::positionRoundPlayer() const{
    return m_positionRoundPlayer;
}

void Collision::setPositionRoundPlayer(const glm::vec3 &position){
    m_positionRoundPlayer = glm::round(position);
}

float Collision::stepMoveAnticipated() const{
    return m_stepMoveAnticipated;
}

void Collision::setStepMoveAnticipated(float anticipatedMove){
    m_stepMoveAnticipated = anticipatedMove;
}

bool Collision::isCubePresent(int x, int y, int z) const{
    if(x<0 || y<0 || z<0)
        return true;

    if(Game::singletonGame()->voxels()[x][y][z]  == nullptr &&
       Game::singletonGame()->voxels()[x][y+1][z]== nullptr )
        return false;

    return true;
}

bool Collision::isImpactFront() const{
    int z = round(m_player.position().z + m_stepMoveAnticipated);
    return this->isCubePresent(m_positionRoundPlayer.x,m_positionRoundPlayer.y,z);
}

bool Collision::isImpactBack() const {
    int z = round(m_player.position().z - m_stepMoveAnticipated);
    return this->isCubePresent(m_positionRoundPlayer.x,m_positionRoundPlayer.y,z);
}

bool Collision::isImpactLeft() const {
    int x = round(m_player.position().x + m_stepMoveAnticipated);
    return this->isCubePresent(x,m_positionRoundPlayer.y,m_positionRoundPlayer.z);
}

bool Collision::isImpactRight() const{
    int x = round(m_player.position().x - m_stepMoveAnticipated);
    return this->isCubePresent(x,m_positionRoundPlayer.y,m_positionRoundPlayer.z);
}

bool Collision::isFalling() const{
    //more readable
    int x = m_positionRoundPlayer.x;
    int y = round(m_player.position().y - m_stepMoveAnticipated);
    int z = m_positionRoundPlayer.z;

    if(y>0 && Game::singletonGame()->voxels()[x][y][z] == nullptr)
        return true;

    return 0;
}

bool Collision::isImpactUp() const{
    //more readable
    int x = m_positionRoundPlayer.x;
    int y = round(m_player.position().y + m_stepMoveAnticipated + 1.6);
    int z = m_positionRoundPlayer.z;

    if(y>0 && Game::singletonGame()->voxels()[x][y][z] == nullptr)
        return false;

    return true;
}













