#pragma once
#include <iostream>
#include <glimac/glm.hpp>

#include "CubeData.hpp"

class CubeFoundation : public CubeData{

    protected:
        int durability() const;

	public:
        CubeFoundation(glm::vec3 const& position, GLint idTexture);
};
