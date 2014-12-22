#include "CubeRock.hpp"

CubeRock::CubeRock(glm::vec3 const& position, GLint idTexture) : CubeData(position, false, this->durability(), idTexture) {}

int CubeRock::durability() const{
    return 15;
}
