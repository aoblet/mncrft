#include "CubeSand.hpp"

CubeSand::CubeSand(glm::vec3 const& position, GLint idTexture) : CubeData(position, false, this->durability(), idTexture) {}

int CubeSand::durability() const{
    return 5;
}
