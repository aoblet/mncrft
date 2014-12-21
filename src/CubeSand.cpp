#include "CubeSand.hpp"

CubeSand::CubeSand() : CubeData::CubeData(m_position, m_gravity, m_life, m_idTexture) {}

int CubeSand::durability() const{
    return -1;
}
