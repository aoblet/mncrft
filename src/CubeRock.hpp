#pragma once
#include <iostream>
#include <glimac/glm.hpp>

#include "CubeData.hpp"

class CubeRock : public CubeData{

    protected:
        int durability() const;

	public:
        CubeRock();
};
