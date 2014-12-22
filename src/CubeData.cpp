#include "CubeData.hpp"
#include <iostream>
#include <cmath>
#include <cstddef>
CubeData::CubeData( glm::vec3 const& position, bool gravity, int life, GLint idTexture):
                    m_position(position), m_gravity(gravity), m_life(life),
                    m_idTexture(idTexture), m_currentLevel_texture(CubeData::maxLevels_texture){}

CubeData::~CubeData(){}

glm::vec3 CubeData::position() const{
	return this->m_position;
}

float CubeData::life() const{
    return this->m_life;
}

GLint CubeData::idTexture() const{
    return this->m_idTexture;
}

int CubeData::currentLevel_texture() const{
    return this->m_currentLevel_texture;
}

void CubeData::setPosition(const glm::vec3 &pos){
	this->m_position = pos;
}

void CubeData::setIdTexture(GLint idText){
    this->m_idTexture = idText;
}

int CubeData::computeCurrentLevel_texture() const{
    return round( this->m_life * CubeData::maxLevels_texture / this->durability());
}

void CubeData::inflictDamage(float damage){
    this->m_life -= damage;
    //compute level with percentage
    this->m_currentLevel_texture = this->computeCurrentLevel_texture();
}
