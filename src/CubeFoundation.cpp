#include "CubeFoundation.hpp"

CubeFoundation::CubeFoundation(glm::vec3 const& position, GLint idTexture) : CubeData(position, false, this->durability(), idTexture) {}

int CubeFoundation::durability() const{
    return -1;
}
