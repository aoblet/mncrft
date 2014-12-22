#include "CubeDirt.hpp"

CubeDirt::CubeDirt(glm::vec3 const& position, GLint idTexture) : CubeData(position, false, this->durability(), idTexture) {}

int CubeDirt::durability() const{
    return 5;
}
