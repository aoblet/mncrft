#include <GL/glew.h>
#include "glimac/Skybox.hpp"
#include <string>
#include "glimac/glm.hpp"
#include <stdexcept>
#include <iostream>
#include "Game.hpp"
#include "Textures.hpp"

namespace glimac{
    int Skybox::RAND_UNIVERS = 0;

    struct Vertex3DCube{
        glm::vec3 m_position;
        glm::vec2 m_txcoord;

        Vertex3DCube(glm::vec3 m_position, glm::vec2 m_txcoord):
           m_position(m_position), m_txcoord(m_txcoord) {}
    };

    Skybox::Skybox(const std::string &currentDirectory, const std::string &nameShader, const Game &game){
        glimac::FilePath applicationPath(currentDirectory);

        std::cout << applicationPath.dirPath() + "/shaders/cubeMap.vs.glsl" << std::endl;
        m_program = glimac::loadProgram(applicationPath.dirPath() + ("/shaders/"+nameShader+".vs.glsl"),
                                        applicationPath.dirPath() + ("/shaders/"+nameShader+".fs.glsl"));

        m_globalUniformBlockIndex = glGetUniformBlockIndex(m_program.getGLId(), "GlobalMatrices");
        glBindBuffer(GL_UNIFORM_BUFFER, game.m_ProgramShader_main.m_ubo_matricesGlobales);
        glUniformBlockBinding(m_program.getGLId(), m_globalUniformBlockIndex, 0);
        glBindBufferRange(GL_UNIFORM_BUFFER, 0, game.m_ProgramShader_main.m_ubo_matricesGlobales, 0, sizeof(glm::mat4) * 2);
        this->bindSkyboxBuffer();
        this->loadSkyboxTexture();
    }

    Skybox::~Skybox(){
        glDeleteBuffers(1, &m_skyboxVBO);
        glDeleteVertexArrays(1, &m_skyboxVAO);
    }

    void Skybox::renderSkybox(){
        m_program.use();
        glDisable(GL_DEPTH_TEST);
        glBindVertexArray(m_skyboxVAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_textures);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        glBindVertexArray(0);
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);
    }

    void Skybox::loadSkyboxTexture(){

        std::vector<std::string> imgFile;

        imgFile.push_back("left.png");
        imgFile.push_back("right.png");

        imgFile.push_back("top.png");
        imgFile.push_back("bottom.png");
        imgFile.push_back("front.png");
        imgFile.push_back("back.png");

        glGenTextures(1, &m_textures);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_textures);
        int indexUniverse = !(Skybox::RAND_UNIVERS%Textures::UNIVERS.size()) ? 0 :1;
        for(int i = 0; i<6; i++){
            auto skBTex = loadImage("assets/textures/skybox/"+Textures::UNIVERS[indexUniverse]+"/"+imgFile[i]);

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, skBTex->getWidth(), skBTex->getHeight(), 0, GL_RGBA, GL_FLOAT, skBTex->getPixels());
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    void Skybox::bindSkyboxBuffer(){

        glm::vec3 skyboxVertices[] = {
            // Positions
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f, -1.0f),
            glm::vec3(1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),

            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),

            glm::vec3(1.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f,  1.0f),
            glm::vec3(1.0f,  1.0f,  1.0f),
            glm::vec3(1.0f,  1.0f,  1.0f),
            glm::vec3(1.0f,  1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f, -1.0f),

            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(1.0f,  1.0f,  1.0f),
            glm::vec3(1.0f,  1.0f,  1.0f),
            glm::vec3(1.0f, -1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),

            glm::vec3(-1.0f,  1.0f, -1.0f),
            glm::vec3(1.0f,  1.0f, -1.0f),
            glm::vec3(1.0f,  1.0f,  1.0f),
            glm::vec3(1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f),

            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(1.0f, -1.0f, -1.0f),
            glm::vec3(1.0f, -1.0f, -1.0f),
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3(1.0f, -1.0f,  1.0f)
        };

        // Setup skybox VAO
        //GLuint skyboxVAO, skyboxVBO;
        glGenVertexArrays(1, &m_skyboxVAO);
        glGenBuffers(1, &m_skyboxVBO);
        glBindVertexArray(m_skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_skyboxVBO);
        glEnableVertexAttribArray(0);

        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
        glBindVertexArray(0);
    }

    void Skybox::changeUniverse(){
        Skybox::RAND_UNIVERS ++;
        glDeleteTextures(1,&m_textures);
        glGenTextures(1,&m_textures);
        this->loadSkyboxTexture();
    }
}
