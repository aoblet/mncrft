#pragma once
#include <iostream>
#include <glimac/glm.hpp>

#include "CubeData.hpp"

class CubeSand : public CubeData{

    protected:
        int durability() const;

	public:
        CubeSand(glm::vec3 const& position, GLint idTexture);
};
