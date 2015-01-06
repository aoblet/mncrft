#include <GL/glew.h>
#include "glimac/Skybox.hpp"

#include "glimac/glm.hpp"
#include <stdexcept>
#include <iostream>

namespace glimac{

    struct Vertex3DCube{
        glm::vec3 m_position;
        glm::vec2 m_txcoord;

        Vertex3DCube(glm::vec3 m_position, glm::vec2 m_txcoord):
           m_position(m_position), m_txcoord(m_txcoord) {}
    };

    Skybox::~Skybox(){
        glDeleteBuffers(1, &m_skyboxVBO);
        glDeleteVertexArrays(1, &m_skyboxVAO);
    }

    void Skybox::renderSkybox(GLuint &texture){
        glDepthMask(GL_FALSE);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glBindVertexArray(m_skyboxVAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        glBindVertexArray(0);
        glDepthMask(GL_TRUE);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
    }

    void Skybox::loadSkyboxTexture(GLuint &texture, FilePath path){

        std::vector<std::string> imgFile;

        imgFile.push_back("right.png");
        imgFile.push_back("left.png");
        imgFile.push_back("top.png");
        imgFile.push_back("bottom.png");
        imgFile.push_back("front.png");
        imgFile.push_back("back.png");

        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

        for(int i = 0; i<6; i++){
            auto skBTex = loadImage(path + "/assets/textures/skybox/"+imgFile[i]);

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, skBTex->getWidth(), skBTex->getHeight(), 0, GL_RGBA, GL_FLOAT, skBTex->getPixels());
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    void Skybox::bindSkyboxBuffer(GLuint &cubeVBO, GLuint &cubeVAO){

        Vertex3DCube cubeVertices[] = {
                                    // Positions          // Texture Coords
           Vertex3DCube(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),
           Vertex3DCube(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)),
           Vertex3DCube(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
           Vertex3DCube(glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)),
           Vertex3DCube(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
           Vertex3DCube(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)),

           Vertex3DCube(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
           Vertex3DCube(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
           Vertex3DCube(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f)),
           Vertex3DCube(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f)),
           Vertex3DCube(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f)),
           Vertex3DCube(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),

           Vertex3DCube(glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
           Vertex3DCube(glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)),
           Vertex3DCube(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)),
           Vertex3DCube(glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)),
           Vertex3DCube(glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)),
           Vertex3DCube(glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),

           Vertex3DCube(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
           Vertex3DCube(glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)),
           Vertex3DCube(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)),
           Vertex3DCube(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f)),
           Vertex3DCube(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f)),
           Vertex3DCube(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),

           Vertex3DCube(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
           Vertex3DCube(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)),
           Vertex3DCube(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
           Vertex3DCube(glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
           Vertex3DCube(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
           Vertex3DCube(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),

           Vertex3DCube(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)),
           Vertex3DCube(glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f)),
           Vertex3DCube(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
           Vertex3DCube(glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f)),
           Vertex3DCube(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f)),
           Vertex3DCube(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f))
               };

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

        // Setup cubeMap VAO
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        glBindVertexArray(cubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DCube), (GLvoid*) offsetof(Vertex3DCube, m_position));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DCube), (GLvoid*) offsetof(Vertex3DCube, m_txcoord));
        glBindVertexArray(0);

        // Setup skybox VAO
        //GLuint skyboxVAO, skyboxVBO;
        glGenVertexArrays(1, &m_skyboxVAO);
        glGenBuffers(1, &m_skyboxVBO);
        glBindVertexArray(m_skyboxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_skyboxVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
        glBindVertexArray(0);
    }


}
