#include <GL/glew.h>
#include "Game.hpp"
#include "CubeData.hpp"
#include "CubeDirt.hpp"
#include "CubeSand.hpp"
#include "Textures.hpp"
#include <glimac/CubeGL.hpp>

void Game::initScene(const Level &level){
    //m_cube_list = std::move(level.cubeList());
    //m_light_list = std::move(level.lightList());
    //m_cubeGL.generateVbo(&m_vbo_cubeGL);
    //m_cubeGL.generateVao(&m_vao_cubeGL,m_vbo_cubeGL,Game::CUBEGL_VERTEX_ATTRIBUT_POSITION,Game::CUBEGL_VERTEX_ATTRIBUT_TEXTURE);

}

Game::Game(const std::string &currentDir, bool test):m_textures(!test),m_ProgramShader_main(currentDir,"tex3D"){
    glGenVertexArrays(1,&m_vao);
}
Game::~Game(){
    glDeleteBuffers(1,&m_vao);
}

void Game::generateGridTest(){
    m_cubeGL_model.configureVao(&m_vao, Game::CUBEGL_VERTEX_ATTRIBUT_POSITION,
                                        Game::CUBEGL_VERTEX_ATTRIBUT_NORMAL,
                                        Game::CUBEGL_VERTEX_ATTRIBUT_TEXTURE);

    m_textures.setUpTexturesTEST(
      "assets/textures/dust.png",
      "assets/textures/dirt.png"
    );

    int y=0;
    for(int x=0; x<100; ++x){
        for(int z=0; z<100; ++z){
            m_cube_list.push_back(CubeDirt(glm::vec3(x,0,z),1));
            if(x%2)
                m_cube_list.push_back(CubeSand(glm::vec3(x,1,z),0));
        }
    }

    glBindVertexArray(m_vao);

    glGenBuffers(1,&m_vbo_cubeData);
    // Binding buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_cubeData);
    // Binding data
    glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(CubeData) * m_cube_list.size(),
      &m_cube_list[0],
      GL_DYNAMIC_DRAW
    );

    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_POSITION);

    // Describing data
    glVertexAttribPointer(
      Game::VOXEL_ATTRIBUT_POSITION,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(CubeData),
      (const GLvoid*) offsetof(CubeData, m_position)
    );

    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_TEXTURE_ID);

    glVertexAttribPointer(
      Game::VOXEL_ATTRIBUT_TEXTURE_ID,
      1,
      GL_FLOAT,
      GL_FALSE,
      sizeof(CubeData),
      (const GLvoid*) offsetof(CubeData, m_idTexture)
    );

    // Iterate for each instance (instanced rendering stuff)
    glVertexAttribDivisor(Game::VOXEL_ATTRIBUT_POSITION, 1);
    glVertexAttribDivisor(Game::VOXEL_ATTRIBUT_TEXTURE_ID, 1);
    glBindVertexArray(0);
}
