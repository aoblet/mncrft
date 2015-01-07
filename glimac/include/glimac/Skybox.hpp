#pragma once
#include "glimac/common.hpp"
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <vector>
#include "Game.hpp"

namespace glimac {

    class Skybox{

        public:
            Skybox(const std::string &currentDirectory, const std::string &nameShader, Game const& game);
            ~Skybox();

            GLuint m_skyboxVBO;
            GLuint m_skyboxVAO;
            GLuint m_textures;

            Program m_shaderProgram;
            GLuint m_globalUniformBlockIndex;
            glimac::Program m_program;

            static int RAND_UNIVERS;

            void renderSkybox();
            void loadSkyboxTexture();
            void bindSkyboxBuffer();
            void changeUniverse();
    };
}
