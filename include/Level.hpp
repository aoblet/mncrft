#pragma once
#include "File.hpp"
#include <string>
#include <map>
#include "CubeData.hpp"
#include "CubeLight.hpp"
#include <json/value.h>
#include <iterator>

class Game;
class Player;
class Level{
    private:
        std::string m_pathFile;
        std::map<int,std::string> m_arrayTypes_cubes;

        template<typename T>
        void cubesObjectToJsonArray(Json::Value& arrayCubes, T begin, T end);
    public:
        Level();
        void test_cubesToJson(bool save=true);
        void test_jsonToCubes(std::string const& filePath);
        void gameToJson(Game const& game, std::string const& filePath, bool save=false, bool readable=true);
        void jsonToCubes(std::string const& filePath, std::vector<CubeData> & cubeDataOutput, std::vector<CubeLight> & cubeLightOutput);
        void jsonToPlayerPosition(std::string const& filePath, Player & player);
};
