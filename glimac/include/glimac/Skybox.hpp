#pragma once
#include "glimac/common.hpp"
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <vector>

namespace glimac {

    class Skybox{

        public:
            Skybox();
            ~Skybox();

            void renderSkybox(GLuint &skyboxVAO, GLuint &texture);
            void deleteSkybox(GLuint &skyboxVBO, GLuint &skyboxVAO);
            void loadSkyboxTexture(GLuint &texture, FilePath path);
            void bindSkyboxBuffer(GLuint &cubeVBO, GLuint &cubeVAO, GLuint &skyboxVBO, GLuint &skyboxVAO);

    };
}
