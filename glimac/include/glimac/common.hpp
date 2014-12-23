#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    ShapeVertex(){}
    ShapeVertex(glm::vec3 const& pos, glm::vec3 const& nor, glm::vec2 const& tex):  position(pos),
                                                                                    normal(nor),
                                                                                    texCoords(tex){}
};

}
