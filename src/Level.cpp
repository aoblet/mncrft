#include "Level.hpp"
#include "CubeData.hpp"
#include "CubeDirt.hpp"
#include "CubeSand.hpp"
#include "CubeRock.hpp"
#include "CubeLight.hpp"
#include "CubeFoundation.hpp"
#include <json/value.h>
#include <iostream>
#include <json/writer.h>
#include <json/reader.h>
#include "Textures.hpp"
#include "Game.hpp"
#include <set>

void output(const Json::Value & value){
    // querying the json object is very simple
    std::cout << value["hello"];
    std::cout << value["number"];
    std::cout << value["array"][0] << value["array"][1];
    std::cout << value["object"]["hello"];
}

Level::Level(){
    //init array
    m_arrayTypes_cubes.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_DIRT,"CubeDirt"));
    m_arrayTypes_cubes.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_FOUNDATION,"CubeFoundation"));
    m_arrayTypes_cubes.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_LIGHT,"CubeLight"));
    m_arrayTypes_cubes.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_ROCK,"CubeRock"));
    m_arrayTypes_cubes.insert(std::pair<int,std::string>(Textures::INDEX_TEXTURE_SAND,"CubeSand"));
}

template<typename T>
void Level::cubesObjectToJsonArray(Json::Value& arrayCubes, T begin, T end){
    while(begin != end){
        if(round(begin->position().x )!= -1){
            Json::Value jsonObject;
            Json::Value position;

            position["x"]=begin->position().x;
            position["y"]=begin->position().y;
            position["z"]=begin->position().z;

            jsonObject["type"] = m_arrayTypes_cubes[begin->idTexture()];
            jsonObject["position"] = position;
            arrayCubes.append(jsonObject);
        }
        ++begin;
    }
}


void Level::gameToJson(const Game &game, const std::string &filePath, bool save, bool readable){
    Json::Value fromScratch;
    Json::Value arrayCubes;

    //cubeData
    this->cubesObjectToJsonArray(arrayCubes, game.m_cube_list.begin(),game.m_cube_list.end());

    //cubeLight
    this->cubesObjectToJsonArray(arrayCubes, game.m_light_list.begin(),game.m_light_list.end());


    //Player
    fromScratch["Player"]["position"]["x"] = game.player().position().x;
    fromScratch["Player"]["position"]["y"] = game.player().position().y;
    fromScratch["Player"]["position"]["z"] = game.player().position().z;

    fromScratch["Player"]["camera"]["phi"] = game.player().camera().phi();
    fromScratch["Player"]["camera"]["theta"] = game.player().camera().theta();


    fromScratch["Cubes"] = arrayCubes;
    if(save){
        // write in a nice readible way
        Json::Writer * jsonWriter; //abstract

        if(readable)
            jsonWriter = new Json::StyledWriter;
        else
            jsonWriter = new Json::FastWriter;

        File::write(filePath,jsonWriter->write(fromScratch));
        delete jsonWriter;
    }
}


void Level::jsonToCubes(std::string const& filePath, std::vector<CubeData> & cubeDataOutput, std::vector<CubeLight> & cubeLightOutput){
    Json::Reader reader;
    Json::Value parsedFromString;
    std::string jsonString;
    File::read(filePath,jsonString);

    if(!(reader.parse(jsonString,parsedFromString)))
        throw std::invalid_argument("fail to parse json");

    Json::Value rootCubes = parsedFromString["Cubes"];
    for(Json::Value::iterator it=rootCubes.begin(); it != rootCubes.end(); ++it){
        int x = (*it)["position"]["x"].asInt();
        int y = (*it)["position"]["y"].asInt();
        int z = (*it)["position"]["z"].asInt();
        glm::vec3 position = glm::vec3(x,y,z);

        std::string type = (*it)["type"].asString() ;
        CubeData * tmp = nullptr;
        CubeLight * tmpLight = nullptr;

        if(type=="CubeDirt")
            tmp = new CubeDirt(position,Textures::INDEX_TEXTURE_DIRT);
        else if(type=="CubeLight")
            tmpLight = new CubeLight(position,Textures::INDEX_TEXTURE_LIGHT);
        else if(type=="CubeFoundation")
            tmp = new CubeFoundation(position,Textures::INDEX_TEXTURE_FOUNDATION);
        else if(type=="CubeRock")
            tmp = new CubeRock(position,Textures::INDEX_TEXTURE_ROCK);
        else if(type=="CubeSand")
            tmp = new CubeSand(position,Textures::INDEX_TEXTURE_SAND);
        else
            continue;

        if(tmp){
            cubeDataOutput.push_back(*tmp);
            delete tmp;
            tmp = nullptr;
        }
        else if(tmpLight){
            cubeLightOutput.push_back(*tmpLight);
            delete tmpLight;
            tmpLight = nullptr;
        }
        else
            throw std::logic_error("Level:jsonToCubes(): error: bad type of cube: see sources for details Level.cpp");
    }
}

void Level::jsonToPlayerPosition(std::string const& filePath, Player & player){
    Json::Reader reader;
    Json::Value parsedFromString;
    std::string jsonString;
    File::read(filePath,jsonString);

    if(!(reader.parse(jsonString,parsedFromString)))
        throw std::invalid_argument("fail to parse json");

    Json::Value rootPlayer = parsedFromString["Player"];
    if(rootPlayer.size() == 0)
        return;

    //position player
    glm::vec3 newPosition = glm::vec3(rootPlayer["position"]["x"].asFloat(),
                                      rootPlayer["position"]["y"].asFloat(),
                                      rootPlayer["position"]["z"].asFloat());
    player.setPosition(newPosition);

    //camera config
    Json::Value cameraConfig;
    if((cameraConfig = rootPlayer["camera"]).size() != 0){
        player.camera().setPhi(cameraConfig["phi"].asFloat());
        player.camera().setTheta(cameraConfig["theta"].asFloat());
    }
}

void Level::test_cubesToJson(bool save){

    std::vector<CubeData> list;
    std::vector<CubeLight> listLight;
    for(int i=0; i<10; ++i){
        list.push_back(CubeDirt(glm::vec3(i,i,i),Textures::INDEX_TEXTURE_DIRT));
        list.push_back(CubeSand(glm::vec3(i,i,i),Textures::INDEX_TEXTURE_SAND));
        listLight.push_back(CubeLight(glm::vec3(0,0,0),Textures::INDEX_TEXTURE_LIGHT));
    }

    Json::Value fromScratch;
    Json::Value arrayCubes;

    //cubeData
    this->cubesObjectToJsonArray(arrayCubes, list.begin(),list.end());

    //cubeLight
    this->cubesObjectToJsonArray(arrayCubes, list.begin(),list.end());


    fromScratch["Cubes"] = arrayCubes;


    if(save){
        // write in a nice readible way
        Json::StyledWriter styledWriter;
        File::write("../../tests/outputJson/test.json",styledWriter.write(fromScratch));
    }
}


void Level::test_jsonToCubes(std::string const& filePath){
    std::vector<CubeData> list;
    Json::Reader reader;
    Json::Value parsedFromString;
    std::string jsonString;
    File::read(filePath,jsonString);

    if(!(reader.parse(jsonString,parsedFromString)))
        throw std::invalid_argument("fail to parse json: TEST");

    Json::Value rootCubes = parsedFromString["Cubes"];
    for(Json::Value::iterator it=rootCubes.begin(); it != rootCubes.end(); ++it){
        int x = (*it)["position"]["x"].asInt();
        int y = (*it)["position"]["y"].asInt();
        int z = (*it)["position"]["z"].asInt();
        glm::vec3 position = glm::vec3(x,y,z);

        std::string type = (*it)["type"].asString() ;
        CubeData * tmp;

        if(type=="CubeDirt")
            tmp = new CubeDirt(position,Textures::INDEX_TEXTURE_DIRT);
        else if(type=="CubeLight")
            tmp = new CubeLight(position,Textures::INDEX_TEXTURE_LIGHT);
        else if(type=="CubeFoundation")
            tmp = new CubeFoundation(position,Textures::INDEX_TEXTURE_FOUNDATION);
        else if(type=="CubeRock")
            tmp = new CubeLight(position,Textures::INDEX_TEXTURE_ROCK);
        else if(type=="CubeSand")
            tmp = new CubeLight(position,Textures::INDEX_TEXTURE_SAND);
        else
            break;

        list.push_back(*tmp);
        delete tmp;
    }
    std::cout << list.size() << std::endl;
    std::cout << list[5].position() << std::endl;
    std::cout << list[6].durability() << std::endl;
}
