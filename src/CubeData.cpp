#include "CubeData.hpp"
#include <iostream>
#include <cmath>
#include <cstddef>
#include <algorithm>

CubeData::CubeData(glm::vec3 const& position, bool gravity, int life, GLint idTexture, int durability):
                    m_position(position), m_gravity(gravity), m_life(life),
                    m_idTexture(idTexture), m_currentLevel_texture(Textures::SIZE_LEVEL_TEXURES),m_durability(durability){}

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

int CubeData::durability() const{
    return m_durability;
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
    return round( std::max(1.f,this->m_life * Textures::SIZE_LEVEL_TEXURES/ (float)(this->durability())));
}

void CubeData::inflictDamage(float damage){
    this->m_life -= damage;
    //compute level with percentage
    this->m_currentLevel_texture = this->computeCurrentLevel_texture();
}
