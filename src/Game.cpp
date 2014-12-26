#include <GL/glew.h>
#include "Game.hpp"
#include "CubeData.hpp"
#include "CubeDirt.hpp"
#include "CubeSand.hpp"
#include "Textures.hpp"
#include <glimac/CubeGL.hpp>
const int Game::CUBEGL_VERTEX_ATTRIBUT_POSITION = 0;
const int Game::CUBEGL_VERTEX_ATTRIBUT_NORMAL = 1;
const int Game::CUBEGL_VERTEX_ATTRIBUT_TEXTURE = 2;
const int Game::VOXEL_ATTRIBUT_POSITION = 3;
const int Game::VOXEL_ATTRIBUT_TEXTURE_ID = 4;
const int Game::SIZE_MAX_GRID = 500;


void Game::initScene(){
    m_cubeGL_model.configureVao(&m_vao_cubeData,Game::CUBEGL_VERTEX_ATTRIBUT_POSITION,
                                                Game::CUBEGL_VERTEX_ATTRIBUT_NORMAL,
                                                Game::CUBEGL_VERTEX_ATTRIBUT_TEXTURE);

    m_utils.loadCubes(m_fileLoad);
    m_utils.initVoxels();
    m_utils.configureVoxels();
    m_utils.configureVboVaoCubeData();
    m_utils.configureVboVaoCubeLight();
}

Game::Game(const std::string &currentDir, std::string const& fileLoad, const std::string &fileSave, bool test)
           :m_textures(!test), m_ProgramShader_main(currentDir,"tex3D"), m_utils(*this), m_fileLoad(fileLoad), m_fileSave(fileSave) {

    glGenVertexArrays(1,&m_vao_cubeLight);
    glGenVertexArrays(1,&m_vao_cubeData);

    if(test)
        return;

    this->initScene();
}

Game::~Game(){
    m_utils.deleteVboVaoCubeData();
    m_utils.deleteVboVaoCubeCubeLight();
}

void Game::generateGridTest(){
    //configure all stuff inside (vbo-vao cubes)
    glGenVertexArrays(1,&m_vao_cubeData);
    m_cubeGL_model.configureVao(&m_vao_cubeData, Game::CUBEGL_VERTEX_ATTRIBUT_POSITION,
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

    glBindVertexArray(m_vao_cubeData);

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
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}
