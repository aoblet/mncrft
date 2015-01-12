#include "GameUtilities.hpp"
#include "Game.hpp"

GameUtilities::GameUtilities(Game & game):m_game(game){}

void GameUtilities::loadCubes(std::string const& filePath){
    Level level;
    level.jsonToCubes(filePath,m_game.m_cube_list, m_game.m_light_list);
    this->initLights();
}

void GameUtilities::saveGame(std::string const& filePath){
    Level level;
    level.gameToJson(m_game,filePath,true,false);
    std::cout << "SAVE";
}

void GameUtilities::configurePositionPlayer(){
    Level level;
    level.jsonToPlayerPosition(m_game.m_fileLoad,m_game.m_player);
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
        if(x > Game::SIZE_MAX_GRID || y > Game::SIZE_MAX_GRID || z > Game::SIZE_MAX_GRID || m_game.m_voxels[x][y][z] != nullptr)
            continue;
        m_game.m_voxels[x][y][z] = &(*it);
    }

    for(std::vector<CubeLight>::iterator it = m_game.m_light_list.begin(); it != m_game.m_light_list.end() ; ++it){
        int x = it->position().x, y = it->position().y, z= it->position().z;
        if(x <0 || x > Game::SIZE_MAX_GRID || y > Game::SIZE_MAX_GRID || z > Game::SIZE_MAX_GRID || m_game.m_voxels[x][y][z] != nullptr)
            continue;
        m_game.m_voxels[x][y][z] = &(*it);
    }
}


void GameUtilities::configureVboVaoCubeData(){
    glBindVertexArray(m_game.m_vao_cubeData);
    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_POSITION);
    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_TEXTURE_ID);
    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_CURRENT_LEVEL_TEXTURE);

    glGenBuffers(1,&m_game.m_vbo_cubeData);
    //Arbitrary size: 1 millions
    glBindBuffer(GL_ARRAY_BUFFER, m_game.m_vbo_cubeData);
    glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(CubeData) * 10000000,
      NULL,
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

    glVertexAttribPointer(
      Game::VOXEL_ATTRIBUT_CURRENT_LEVEL_TEXTURE,
      1,
      GL_FLOAT,
      GL_FALSE,
      sizeof(CubeData),
      (const GLvoid*) offsetof(CubeData, m_currentLevel_texture)
    );

    // Iterate for each instance (instanced rendering stuff)
    glVertexAttribDivisor(Game::VOXEL_ATTRIBUT_POSITION, 1);
    glVertexAttribDivisor(Game::VOXEL_ATTRIBUT_TEXTURE_ID, 1);
    glVertexAttribDivisor(Game::VOXEL_ATTRIBUT_CURRENT_LEVEL_TEXTURE, 1);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void GameUtilities::configureVboVaoCubeLight(){
    glBindVertexArray(m_game.m_vao_cubeLight);
    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_POSITION);
    glEnableVertexAttribArray(Game::VOXEL_ATTRIBUT_TEXTURE_ID);

    glGenBuffers(1,&m_game.m_vbo_cubeLight);
    glBindBuffer(GL_ARRAY_BUFFER, m_game.m_vbo_cubeLight);
    glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(CubeLight) * m_game.m_light_list.size(),
      &m_game.m_light_list[0],
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

void GameUtilities::deleteVoxels(){
    for(int i=0; i<Game::SIZE_MAX_GRID; ++i){
        for(int j=0; j<Game::SIZE_MAX_GRID; ++j){
            delete[] m_game.m_voxels[i][j];
        }
        delete[] m_game.m_voxels[i];
    }
    delete[] m_game.m_voxels;
}

void GameUtilities::updateVboCubeData(int startPosCube, int endPosCube){
    if(endPosCube < startPosCube || startPosCube <0 || endPosCube<0)
        throw std::invalid_argument("Update vbo cubeData: wrong parameter index cubes");

    glBindBuffer(GL_ARRAY_BUFFER, m_game.m_vbo_cubeData);
    glBufferSubData(
        GL_ARRAY_BUFFER,
        startPosCube*sizeof(CubeData),
        (endPosCube - startPosCube +1)*sizeof(CubeData) ,
        &(m_game.m_cube_list[startPosCube])
    );
    glBindBuffer(GL_ARRAY_BUFFER,0);
}


void GameUtilities::initLights(){
    m_game.m_light_list.resize(CubeLight::MAX_LIGHT,CubeLight(glm::vec3(-1,-1,-1),Textures::INDEX_TEXTURE_LIGHT));

    for(int i=0; i<CubeLight::MAX_LIGHT; ++i){
        m_game.m_uLightsArray[i] = m_game.m_light_list[i].position();
    }
}

void GameUtilities::updateHiddenCubes(){
}

