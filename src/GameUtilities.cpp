#include "GameUtilities.hpp"
#include "Game.hpp"

GameUtilities::GameUtilities(Game & game):m_game(game){}

void GameUtilities::loadCubes(std::string const& filePath){
    Level level;
    level.jsonToCubes(filePath,m_game.m_cube_list, m_game.m_light_list);
}

void GameUtilities::saveCubes(std::string const& filePath){
    Level level;
    level.gameToJson(m_game,filePath,true,true);
}

void GameUtilities::initVoxels(){
    m_game.m_voxels = new CubeData***[Game::SIZE_MAX_GRID];

    for(int i=0; i<Game::SIZE_MAX_GRID; ++i){
        m_game.m_voxels[i] = new CubeData**[Game::SIZE_MAX_GRID]; //1d
        for(int j=0; j<Game::SIZE_MAX_GRID; ++j){
            m_game.m_voxels[i][j] = new CubeData*[Game::SIZE_MAX_GRID]; //2d
            for(int k=0; k<Game::SIZE_MAX_GRID; ++k){
                m_game.m_voxels[i][j][k] = nullptr; //3d
            }
        }
    }
}

void GameUtilities::configureVoxels(){
    for(std::vector<CubeData>::iterator it = m_game.m_cube_list.begin(); it != m_game.m_cube_list.end() ; ++it){
        int x = it->position().x, y = it->position().y, z= it->position().z;
        if(x > Game::SIZE_MAX_GRID || y > Game::SIZE_MAX_GRID || z > Game::SIZE_MAX_GRID)
            break;
        m_game.m_voxels[x][y][z] = &(*it);
    }
}


void GameUtilities::configureVboVaoCubeData(){
    glBindVertexArray(m_game.m_vao_cubeData);
    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_POSITION);
    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_TEXTURE_ID);

    glGenBuffers(1,&m_game.m_vbo_cubeData);
    glBindBuffer(GL_ARRAY_BUFFER, m_game.m_vbo_cubeData);
    glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(CubeData) * m_game.m_cube_list.size(),
      &m_game.m_cube_list[0],
      GL_DYNAMIC_DRAW
    );


    // Describing data
    glVertexAttribPointer(
      Game::VOXEL_ATTRIBUT_POSITION,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(CubeData),
      (const GLvoid*) offsetof(CubeData, m_position)
    );

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

void GameUtilities::configureVboVaoCubeLight(){
    glBindVertexArray(m_game.m_vao_cubeLight);
    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_POSITION);
    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_TEXTURE_ID);

    glGenBuffers(1,&m_game.m_vbo_cubeData);
    glBindBuffer(GL_ARRAY_BUFFER, m_game.m_vbo_cubeData);
    glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(CubeLight) * m_game.m_cube_list.size(),
      &m_game.m_cube_list[0],
      GL_DYNAMIC_DRAW
    );


    // Describing data
    glVertexAttribPointer(
      Game::VOXEL_ATTRIBUT_POSITION,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(CubeLight),
      (const GLvoid*) offsetof(CubeLight, m_position)
    );

    glVertexAttribPointer(
      Game::VOXEL_ATTRIBUT_TEXTURE_ID,
      1,
      GL_FLOAT,
      GL_FALSE,
      sizeof(CubeLight),
      (const GLvoid*) offsetof(CubeLight, m_idTexture)
    );

    // Iterate for each instance (instanced rendering stuff)
    glVertexAttribDivisor(Game::VOXEL_ATTRIBUT_POSITION, 1);
    glVertexAttribDivisor(Game::VOXEL_ATTRIBUT_TEXTURE_ID, 1);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void GameUtilities::deleteVboVaoCubeData(){
    glDeleteBuffers(1,&m_game.m_vbo_cubeData);
    glDeleteBuffers(1,&m_game.m_vao_cubeData);
}

void GameUtilities::deleteVboVaoCubeCubeLight(){
    glDeleteBuffers(1,&m_game.m_vbo_cubeLight);
    glDeleteBuffers(1,&m_game.m_vao_cubeLight);
}
