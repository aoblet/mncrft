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
const int Game::VOXEL_ATTRIBUT_CURRENT_LEVEL_TEXTURE = 5;
const int Game::SIZE_MAX_GRID = 500;
const int Game::FRAME_PER_SECOND = 60;


void Game::initScene(){
    m_cubeGL_model.configureVao(&m_vao_cubeData,Game::CUBEGL_VERTEX_ATTRIBUT_POSITION,
                                                Game::CUBEGL_VERTEX_ATTRIBUT_NORMAL,
                                                Game::CUBEGL_VERTEX_ATTRIBUT_TEXTURE);

    m_utils.configurePositionPlayer();
    m_utils.loadCubes(m_fileLoad);
    m_utils.initVoxels();
    m_utils.configureVoxels();
    m_utils.configureVboVaoCubeData();
    m_utils.configureVboVaoCubeLight();
    m_utils.updateVboCubeData(0,m_cube_list.size());
}

Game::Game(const std::string &currentDir, std::string const& fileLoad, const std::string &fileSave, bool test)
           :m_textures(!test), m_ProgramShader_main(currentDir,"tex3D"), m_utils(*this), m_fileLoad(fileLoad),
            m_fileSave(fileSave), m_test(test),m_player(this,glm::vec3(40,60,50)){

    glGenVertexArrays(1,&m_vao_cubeLight);
    glGenVertexArrays(1,&m_vao_cubeData);

    if(test)
        return;

    this->initScene();
}

Game::~Game(){
    //TODO remove after tests
    if(!m_test){
        m_utils.deleteVboVaoCubeData();
        m_utils.deleteVboVaoCubeCubeLight();
        m_utils.deleteVoxels();
        m_utils.saveGame(m_fileSave);
    }
}

void Game::generateGridTest(){
    //configure all stuff inside (vbo-vao cubes)
    glGenVertexArrays(1,&m_vao_cubeData);
    m_cubeGL_model.configureVao(&m_vao_cubeData, Game::CUBEGL_VERTEX_ATTRIBUT_POSITION,
                                                 Game::CUBEGL_VERTEX_ATTRIBUT_NORMAL,
                                                 Game::CUBEGL_VERTEX_ATTRIBUT_TEXTURE);

    m_textures.setUpTexturesTEST(
      "assets/textures/cubes/foundation/1.png",
      "assets/textures/cubes/foundation/1.png"
    );

    int y=0;
    for(int x=0; x<100; ++x){
        for(int z=0; z<100; ++z){
            m_cube_list.push_back(CubeDirt(glm::vec3(x,0,z),Textures::INDEX_TEXTURE_DIRT));
            if(z<10){
                m_cube_list.push_back(CubeSand(glm::vec3(x,1,z),Textures::INDEX_TEXTURE_SAND));
                m_cube_list.push_back(CubeSand(glm::vec3(x,2,z),Textures::INDEX_TEXTURE_SAND));
                m_cube_list.push_back(CubeSand(glm::vec3(x,3,z),Textures::INDEX_TEXTURE_SAND));

            }

        }
    }

    for(int z=0; z<50; ++z){
        m_cube_list.push_back(CubeSand(glm::vec3(40,z,50),Textures::INDEX_TEXTURE_SAND));
        m_cube_list.push_back(CubeSand(glm::vec3(48,z,50),Textures::INDEX_TEXTURE_SAND));
        m_cube_list.push_back(CubeSand(glm::vec3(489,z,50),Textures::INDEX_TEXTURE_SAND));
    }

    //stair
    m_cube_list.push_back(CubeSand(glm::vec3(1+20,7,5),Textures::INDEX_TEXTURE_SAND));
    m_cube_list.push_back(CubeSand(glm::vec3(1+20,6,6),Textures::INDEX_TEXTURE_SAND));
    m_cube_list.push_back(CubeSand(glm::vec3(1+20,5,7),Textures::INDEX_TEXTURE_SAND));
    m_cube_list.push_back(CubeSand(glm::vec3(1+20,4,8),Textures::INDEX_TEXTURE_SAND));
    m_cube_list.push_back(CubeSand(glm::vec3(1+20,3,9),Textures::INDEX_TEXTURE_SAND));
    m_cube_list.push_back(CubeSand(glm::vec3(1+20,2,10),Textures::INDEX_TEXTURE_SAND));
    m_cube_list.push_back(CubeSand(glm::vec3(1+20,1,11),Textures::INDEX_TEXTURE_SAND));
    m_cube_list.push_back(CubeSand(glm::vec3(2+20,1,12),Textures::INDEX_TEXTURE_SAND));
    m_cube_list.push_back(CubeSand(glm::vec3(3+20,1,13),Textures::INDEX_TEXTURE_SAND));
    m_cube_list.push_back(CubeSand(glm::vec3(2+20,1,14),Textures::INDEX_TEXTURE_SAND));

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

CubeData* *** const Game::voxels() const{
    return m_voxels;
}

std::vector<Player> &Game::players(){
    return m_players;
}


std::vector<Player> Game::players() const{
    return m_players;
}

Player& Game::player(){
    return m_player;
}

Player Game::player() const{
    return m_player;
}

GameUtilities &Game::utils(){
    return m_utils;
}

Textures& Game::textures(){
    return m_textures;
}

void Game::renderGame(){
    m_ProgramShader_main.m_program.use();
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->textures().idTexture());
    glBindVertexArray(m_vao_cubeData);
    glDrawArraysInstanced(GL_TRIANGLES, 0, m_cubeGL_model.sizeVertices(), m_cube_list.size());
}
