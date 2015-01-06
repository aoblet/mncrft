#pragma once

#include "CubeData.hpp"
#include "CubeLight.hpp"
#include "Player.hpp"
#include "GameUtilities.hpp"
#include "File.hpp"
#include "Level.hpp"
#include "glimac/CubeGL.hpp"
#include <vector>
#include "ProgramShader_main.hpp"
#include "CubeLight.hpp"


class Game{
    private:
        CubeData* ***m_voxels ; //pointers in 3d
        time_t m_time; //timestamp

        GameUtilities m_utils;
        std::string m_fileLoad;
        std::string m_fileSave;
        bool m_test;
        Player m_player;
        Textures m_textures;

    public:
        std::vector<CubeData> m_cube_list;
        std::vector<CubeData*> m_cubes_removed;
        std::vector<CubeLight> m_light_list;
        glm::vec3 m_uLightsArray[CubeLight::MAX_LIGHT];

        std::vector<Player> m_players;

        ProgramShader_main m_ProgramShader_main;
        glimac::CubeGL m_cubeGL_model;

        GLuint m_vao_cubeLight;
        GLuint m_vbo_cubeLight;
        GLuint m_vao_cubeData;
        GLuint m_vbo_cubeData;


        Game(std::string const& currentDir, const std::string &fileLoad, const std::string &fileSave, bool test=false);
        ~Game();

        Textures& textures();
        std::vector<Player>& players();
        std::vector<Player> players() const;

        Player& player();
        Player player() const;
        GameUtilities& utils();
        CubeData* *** const voxels() const;

        void initScene();
        void generateGridTest();

        static const int CUBEGL_VERTEX_ATTRIBUT_POSITION ;
        static const int CUBEGL_VERTEX_ATTRIBUT_NORMAL ;
        static const int CUBEGL_VERTEX_ATTRIBUT_TEXTURE;
        static const int VOXEL_ATTRIBUT_POSITION ;
        static const int VOXEL_ATTRIBUT_TEXTURE_ID;
        static const int VOXEL_ATTRIBUT_CURRENT_LEVEL_TEXTURE;
        static const int SIZE_MAX_GRID ;
        static const int FRAME_PER_SECOND ;

        friend class GameUtilities;

};
