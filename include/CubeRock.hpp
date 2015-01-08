#pragma once
#include <iostream>
#include <glimac/glm.hpp>

#include "CubeData.hpp"

class CubeRock : public CubeData{
	public:
        CubeRock(glm::vec3 const& position, GLint idTexture);
};
