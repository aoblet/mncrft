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

            GLuint m_skyboxVBO;
            GLuint m_skyboxVAO;

            void renderSkybox(GLuint &texture);
            void loadSkyboxTexture(GLuint &texture, FilePath path);
            void bindSkyboxBuffer(GLuint &cubeVBO, GLuint &cubeVAO);

    };
}
