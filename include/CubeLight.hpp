#pragma once
#include "CubeData.hpp"
#include <glimac/glm.hpp>

class CubeLight: public CubeData{
    public:
        int durability() const;
        CubeLight(glm::vec3 const& post, GLint idTexture);

};
