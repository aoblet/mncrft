#include "GameInteraction.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "CubeDirt.hpp"
#include "CubeRock.hpp"
#include "CubeLight.hpp"
#include "CubeSand.hpp"
#include "CubeFoundation.hpp"
#include "Textures.hpp"

GameInteraction::GameInteraction(Player &player):m_player(player){
    //we want 3 interactions per second
    m_lockClickFrameDuration = Game::FRAME_PER_SECOND / 3;
    m_currentLockClickFrame = 0;
}

int  GameInteraction::distanceIntersectionCube(int distanceMax) const{
    glm::vec3 positionToCompare_voxelSpace;
    glm::vec3 lookAtNormalize = glm::normalize(m_player.camera().frontVector());

    for(int i=1; i<distanceMax+1; ++i){
        positionToCompare_voxelSpace =  glm::round(m_player.camera().position() + ((float)(i)*lookAtNormalize));

        if(positionToCompare_voxelSpace.x <0 || positionToCompare_voxelSpace.y <0 || positionToCompare_voxelSpace.z <0)
            return -1;

        if(m_player.game()->voxels()[(int)positionToCompare_voxelSpace.x]
                                    [(int)positionToCompare_voxelSpace.y]
                                    [(int)positionToCompare_voxelSpace.z] != nullptr){
            return i;
        }
    }

    return -1;
}

void GameInteraction::addCube(glm::vec3 const& positionVoxel, CubeType const& type){
    int x = positionVoxel.x; //cast in int for voxels ref && more readable
    int y = positionVoxel.y;
    int z = positionVoxel.z;

    if(x <0 || y<0 || z<0 || m_player.game()->voxels()[x][y][z] != nullptr)
        return;

    glm::vec3 posEyePlayerRound = glm::round(m_player.camera().position());
    glm::vec3 posPlayerRound = glm::round(m_player.position());

    if(x==(int)posEyePlayerRound.x && y==(int)posEyePlayerRound.y && z==(int)posEyePlayerRound.z)
        return;

    if(x==(int)posPlayerRound.x && y==(int)posPlayerRound.y && z==(int)posPlayerRound.z)
        return;

    CubeData * cubeToAdd;

    if(type == CubeType::DIRT)
        cubeToAdd = new CubeDirt(positionVoxel, Textures::INDEX_TEXTURE_DIRT);
    else if(type == CubeType::SAND)
        cubeToAdd = new CubeSand(positionVoxel, Textures::INDEX_TEXTURE_SAND);
    else if(type == CubeType::ROCK)
        cubeToAdd = new CubeRock(positionVoxel, Textures::INDEX_TEXTURE_ROCK);
    else if(type == CubeType::LIGHT)
        cubeToAdd = new CubeLight(positionVoxel, Textures::INDEX_TEXTURE_LIGHT);
    else if(type == CubeType::FOUNDATION)
        cubeToAdd = new CubeFoundation(positionVoxel, Textures::INDEX_TEXTURE_FOUNDATION);
    else
        return;

    CubeData * refToAdd = nullptr;
    int posCubeUpdateVBO;
    if(m_player.game()->m_cubes_removed.size() != 0){
        refToAdd = m_player.game()->m_cubes_removed.back();
        m_player.game()->m_cubes_removed.pop_back();
        *refToAdd = *cubeToAdd;
        posCubeUpdateVBO = refToAdd - m_player.game()->m_cube_list.data();
    }
    else{
        m_player.game()->m_cube_list.push_back(*cubeToAdd);
        refToAdd = &(m_player.game()->m_cube_list.back());
        posCubeUpdateVBO = m_player.game()->m_cube_list.size() -1 ;
    }

    delete cubeToAdd;

    m_player.game()->voxels()[x][y][z] =refToAdd;
    m_player.game()->utils().updateVboCubeData(posCubeUpdateVBO,posCubeUpdateVBO);
}

void GameInteraction::hitCube(glm::vec3 const& positionVoxel){
    int x = positionVoxel.x; //cast in int for voxels ref && more readable
    int y = positionVoxel.y;
    int z = positionVoxel.z;

    if(x <=0 || y<=0 || z<=0)
        return;

    CubeData* refVoxel = m_player.game()->voxels()[x][y][z];

    //durability -1 : foundation
    if(!refVoxel || refVoxel->durability() == -1)
        return;

    std::cout << x <<"; " << y << ", " << z << std::endl;

    refVoxel->inflictDamage(0.2);
    if(refVoxel->life() > 0)
        return;

    m_player.game()->voxels()[x][y][z] = nullptr;
    refVoxel->setPosition(glm::vec3(0,0,0));
    m_player.game()->m_cubes_removed.push_back(refVoxel);

    int cubePosToUpdate = refVoxel - m_player.game()->m_cube_list.data();
    m_player.game()->utils().updateVboCubeData(cubePosToUpdate,cubePosToUpdate);
}

void GameInteraction::handleInteraction(glimac::SDLWindowManager const& events){
    //TODO : add current typeCube for player

    //more readable
    bool isMouseRightPressed = events.isMouseButtonPressed(SDL_BUTTON_RIGHT);
    bool isMouseLeftPressed  = events.isMouseButtonPressed(SDL_BUTTON_LEFT);


    if(!isMouseRightPressed && !isMouseLeftPressed)
        m_currentLockClickFrame = 0;

    if(m_currentLockClickFrame != 0 && m_currentLockClickFrame < m_lockClickFrameDuration){
        ++m_currentLockClickFrame;
        return;
    }
    m_currentLockClickFrame = 0;

    if(isMouseRightPressed && !isMouseLeftPressed){
        m_currentLockClickFrame = 1;
        int distanceIntersect = this->distanceIntersectionCube(4);

        if(distanceIntersect != -1){
            glm::vec3 posVoxelAdd = glm::round(m_player.camera().position() + m_player.camera().frontVector()*((float)(distanceIntersect-1)));
            this->addCube(posVoxelAdd, m_player.currentCubeType());
        }
    }
    else if(isMouseLeftPressed && !isMouseRightPressed){
        m_currentLockClickFrame = 1;
        int distanceIntersect = this->distanceIntersectionCube(4);

        if(distanceIntersect != -1){
            glm::vec3 posVoxelRemove = glm::round(m_player.camera().position() + m_player.camera().frontVector()*((float)distanceIntersect));
            this->hitCube(posVoxelRemove);
        }
    }
}

void GameInteraction::handleChoiceCubeType(SDL_Event const& event){
    int offsetCubeType = (event.button.button == SDL_BUTTON_WHEELUP) ? 1 : -1;

    if(!m_player.currentCubeType() && offsetCubeType < 0 )
        offsetCubeType = CubeType::COUNT-1;

    m_player.setCurrentCubeType((CubeType) ((m_player.currentCubeType()+offsetCubeType) % CubeType::COUNT));
}










