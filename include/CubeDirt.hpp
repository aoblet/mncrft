#pragma once
#include <glimac/glm.hpp>

#include "CubeData.hpp"

class CubeDirt : public CubeData{
	public:
        CubeDirt(glm::vec3 const& position, GLint idTexture);
};
