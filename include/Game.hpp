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


class Game{
    private:
        CubeData* ***m_voxels ; //pointers in 3d
        time_t m_time; //timestamp

        GLuint m_vbo_cubeData;
        GLuint m_vbo_cubeLight;
        GameUtilities m_utils;
        std::string m_fileLoad;
        std::string m_fileSave;
        bool m_test;

    public:
        std::vector<CubeData> m_cube_list;
        std::vector<CubeLight> m_light_list;
        std::vector<Player> m_players;
        Player m_player;

        ProgramShader_main m_ProgramShader_main;
        glimac::CubeGL m_cubeGL_model;

        Textures m_textures;
        GLuint m_vao_cubeData;
        GLuint m_vao_cubeLight;

        Game(std::string const& currentDir, const std::string &fileLoad, const std::string &fileSave, bool test=false);
        ~Game();

        std::vector<Player>& players();
        std::vector<Player> players() const;
        Player& player();
        Player player() const;

        void initScene();
        void generateGridTest();
        CubeData* *** const voxels() const;

        static const int CUBEGL_VERTEX_ATTRIBUT_POSITION ;
        static const int CUBEGL_VERTEX_ATTRIBUT_NORMAL ;
        static const int CUBEGL_VERTEX_ATTRIBUT_TEXTURE;
        static const int VOXEL_ATTRIBUT_POSITION ;
        static const int VOXEL_ATTRIBUT_TEXTURE_ID;
        static const int SIZE_MAX_GRID ;

        friend class GameUtilities;

};
