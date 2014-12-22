#include "CubeRock.hpp"

CubeRock::CubeRock() : CubeData::CubeData(m_position, m_gravity, m_life, m_idTexture) {}

int CubeRock::durability() const{
    return 15;
}
