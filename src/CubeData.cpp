#include "CubeData.hpp"

CubeData::CubeData(glm::vec3 const& position, bool gravity, float life, GLint idTexture) : m_position(position), m_gravity(gravity), m_life(life), m_idTexture(idTexture){}

glm::vec3 CubeData::position() const{
	return this->m_position;
}

float CubeData::life() const{
    return this->m_life;
}

GLint CubeData::idTexture() const{
    return this->m_idTexture;
}

void CubeData::setPosition(glm::vec3 pos){
	this->m_position = pos;
}

void CubeData::setIdTexture(GLint idText){
    this->m_idTexture = idText;
}

void CubeData::setLife(float damage){
    this-> m_life -= damage;
}

