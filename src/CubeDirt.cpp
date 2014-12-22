#include "CubeDirt.hpp"

CubeDirt::CubeDirt() : CubeData::CubeData(m_position, m_gravity, m_life, m_idTexture) {}

int CubeDirt::durability() const{
    return 5;
}
