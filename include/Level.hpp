#pragma once
#include "File.hpp"
#include <string>
#include <map>
#include "CubeData.hpp"
#include "CubeLight.hpp"
#include <json/value.h>

class Game;

class Level{
    private:
        std::string m_pathFile;
        std::map<int,std::string> m_arrayTypes_cubes;
        void    cubeObjectToJsonObject(CubeData const& cubeObject, Json::Value &jsonObject);
    public:
        Level();
        void test_cubesToJson(bool save=true);
        void test_jsonToCubes(std::string const& filePath);
        void gameToJson(Game const& game, std::string const& filePath, bool save=false);
        void jsonToCubes(std::string const& filePath, std::vector<CubeData> & cubeDataOutput, std::vector<CubeLight> & cubeLightOutput);
};
