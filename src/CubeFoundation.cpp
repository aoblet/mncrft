#include "CubeFoundation.hpp"

CubeFoundation::CubeFoundation() : CubeData::CubeData(m_position, m_gravity, m_life, m_idTexture) {}

int CubeFoundation::durability() const{
    return -1;
}
