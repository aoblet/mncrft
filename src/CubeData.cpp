#include "CubeData.hpp"

//CubeData::CubeData() : m_gravity(false) , m_durability(-1){}

glm::vec3 CubeData::position() const{
	return this->m_position;
}

int CubeData::durability() const{
	return this->m_durability;
}

int CubeData::life() const{
	return this->m_life;
}

void CubeData::setPosition(glm::vec3 pos){
	this->m_position = pos;
}

void CubeData::setLife(int damage){
    this-> m_life -= damage;
}

