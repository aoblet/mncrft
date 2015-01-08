#pragma once
#include <iostream>
#include <glimac/glm.hpp>

#include "CubeData.hpp"

class CubeFoundation : public CubeData{
	public:
        CubeFoundation(glm::vec3 const& position, GLint idTexture);
};
