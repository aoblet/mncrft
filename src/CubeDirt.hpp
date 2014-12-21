#pragma once
#include <iostream>
#include <glimac/glm.hpp>

#include "CubeData.hpp"

class CubeDirt : public CubeData{

    protected:
        int durability() const;

	public:
        CubeDirt();
};
