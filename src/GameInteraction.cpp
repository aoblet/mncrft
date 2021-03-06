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
    m_lockClickFrameDuration = Game::FRAME_PER_SECOND / 5;
    m_currentLockClickFrame = 0;
}

int  GameInteraction::distanceIntersectionCube(int distanceMax) const{
    glm::vec3 positionToCompare_voxelSpace;
    glm::vec3 lookAtNormalize = glm::normalize(m_player.camera().frontVector());

    for(int i=1; i<distanceMax+1; ++i){
        positionToCompare_voxelSpace =  glm::round(m_player.camera().position() + ((float)(i)*lookAtNormalize));

        if(positionToCompare_voxelSpace.x <0 || positionToCompare_voxelSpace.y <0 || positionToCompare_voxelSpace.z <0)
            return -1;

        if(Game::singletonGame()->voxels()[(int)positionToCompare_voxelSpace.x]
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

    if(x <0 || y<0 || z<0 || Game::singletonGame()->voxels()[x][y][z] != nullptr)
        return;

    glm::vec3 posEyePlayerRound = glm::round(m_player.camera().position());
    glm::vec3 posPlayerRound = glm::round(m_player.position());

    if(x==(int)posEyePlayerRound.x && y==(int)posEyePlayerRound.y && z==(int)posEyePlayerRound.z)
        return;
    if(x==(int)posPlayerRound.x && y==(int)posPlayerRound.y && z==(int)posPlayerRound.z)
        return;

    CubeData * cubeToAdd = nullptr;
    if(type == CubeType::DIRT)
        cubeToAdd = new CubeDirt(positionVoxel, Textures::INDEX_TEXTURE_DIRT);
    else if(type == CubeType::SAND)
        cubeToAdd = new CubeSand(positionVoxel, Textures::INDEX_TEXTURE_SAND);
    else if(type == CubeType::ROCK)
        cubeToAdd = new CubeRock(positionVoxel, Textures::INDEX_TEXTURE_ROCK);
    else if(type == CubeType::FOUNDATION)
        cubeToAdd = new CubeFoundation(positionVoxel, Textures::INDEX_TEXTURE_FOUNDATION);
    else if(type != CubeType::LIGHT)
        return;

    CubeData * refToAdd = nullptr;
    int posCubeUpdateVBO;

    if(type == CubeType::LIGHT){
        std::vector<CubeLight>& arrayLight = Game::singletonGame()->m_light_list; //more readable
        //search empty place in vector
        if(arrayLight.size() > CubeLight::MAX_LIGHT)
            throw std::invalid_argument("addCube: bad init of lights");

        int indexFree;
        for(indexFree=0; indexFree<arrayLight.size(); ++indexFree){
            if((int)(arrayLight[indexFree].position().x) == -1)
               break;
        }

        indexFree = indexFree == CubeLight::MAX_LIGHT ? indexFree -1: indexFree; //clamp
        arrayLight[indexFree].setPosition(positionVoxel);
        refToAdd = &(arrayLight[indexFree]);
        Game::singletonGame()->m_uLightsArray[indexFree] = refToAdd->position();
    }
    else{
        //for cubes != light: same operation
        if(Game::singletonGame()->m_cubes_removed.size() != 0){
            refToAdd = Game::singletonGame()->m_cubes_removed.back();
            Game::singletonGame()->m_cubes_removed.pop_back();
            *refToAdd = *cubeToAdd;
            posCubeUpdateVBO = refToAdd - Game::singletonGame()->m_cube_list.data();
        }
        else{
            Game::singletonGame()->m_cube_list.push_back(*cubeToAdd);
            refToAdd = &(Game::singletonGame()->m_cube_list.back());
            posCubeUpdateVBO = Game::singletonGame()->m_cube_list.size() -1 ;
        }
        Game::singletonGame()->utils().updateVboCubeData(posCubeUpdateVBO,posCubeUpdateVBO);
    }

    Game::singletonGame()->voxels()[x][y][z] =refToAdd;
    delete cubeToAdd;
}

void GameInteraction::hitCube(glm::vec3 const& positionVoxel){
    int x = positionVoxel.x; //cast in int for voxels ref && more readable
    int y = positionVoxel.y;
    int z = positionVoxel.z;

    if(x<=0 || y<=0 || z<=0)
        return;

    CubeData* refVoxel = Game::singletonGame()->voxels()[x][y][z];

    //durability -1 : foundation
    if(!refVoxel || refVoxel->durability() == -1)
        return;

    refVoxel->inflictDamage(1);
    if(refVoxel->life() <= 0){
        Game::singletonGame()->voxels()[x][y][z] = nullptr;
        refVoxel->setPosition(glm::vec3(-1,0,0)); //-1 for save file && light

        if(refVoxel->durability() != 1){
            //not light
            Game::singletonGame()->m_cubes_removed.push_back(refVoxel);
//            glm::vec3 rounded = glm::round(glm::normalize(m_player.camera().frontVectorYconstant()));
//            bool lol = false;
//            if(Game::singletonGame()->voxels()[x][y-1][z]  == nullptr && (lol=true)){
//                Game::singletonGame()->m_cube_list.push_back(CubeDirt(glm::vec3(x,y-1,z),Textures::INDEX_TEXTURE_DIRT));
//                Game::singletonGame()->voxels()[x][y-1][z] =  &Game::singletonGame()->m_cube_list.back();
//                Game::singletonGame()->utils().updateVboCubeData(Game::singletonGame()->m_cube_list.size()-1,Game::singletonGame()->m_cube_list.size()-1);

//            }
//            if(Game::singletonGame()->voxels()[int(x+rounded.x)][y-1][int(z+rounded.z)]  == nullptr && (lol=true)){
//                Game::singletonGame()->m_cube_list.push_back(CubeDirt(glm::vec3(x,y-1,z),Textures::INDEX_TEXTURE_DIRT));
//                Game::singletonGame()->voxels()[int(x+rounded.x)][y-1][int(z+rounded.z)] = &Game::singletonGame()->m_cube_list.back();
//                Game::singletonGame()->utils().updateVboCubeData(Game::singletonGame()->m_cube_list.size()-1,Game::singletonGame()->m_cube_list.size()-1);

//            }

        }
        else{
            Game::singletonGame()->m_uLightsArray[(CubeLight*)refVoxel -Game::singletonGame()->m_light_list.data() ] = refVoxel->position();
            return;
        }
    }

    int cubePosToUpdate = refVoxel - Game::singletonGame()->m_cube_list.data();
    Game::singletonGame()->utils().updateVboCubeData(cubePosToUpdate,cubePosToUpdate);
    Game::singletonGame()->utils().updateVboCubeData(Game::singletonGame()->m_cube_list.size()-1,Game::singletonGame()->m_cube_list.size()-1);
}

void GameInteraction::handleInteraction(glimac::SDLWindowManager const& events){

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
        int distanceIntersect = this->distanceIntersectionCube(5);

        if(distanceIntersect != -1){
            glm::vec3 posVoxelAdd = glm::round(m_player.camera().position() + m_player.camera().frontVector()*((float)(distanceIntersect-1)));
            this->addCube(posVoxelAdd, m_player.currentCubeType());
        }
    }
    else if(isMouseLeftPressed && !isMouseRightPressed){
        m_currentLockClickFrame = 1;
        int distanceIntersect = this->distanceIntersectionCube(5);

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










