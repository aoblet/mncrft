#pragma once
#include "CubeData.hpp"
#include <glimac/glm.hpp>

class CubeLight: public CubeData{
    public:
        CubeLight(glm::vec3 const& post, GLint idTexture);

};
