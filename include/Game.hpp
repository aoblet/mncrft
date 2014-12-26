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
        CubeData* *** m_voxels; //pointers in 3d

        time_t m_time; //timestamp
        std::vector<Player*> m_players;

        GLuint m_vbo_cubeData;
        GLuint m_vbo_cubeLight;

    public:
        std::vector<CubeData> m_cube_list;
        std::vector<CubeLight> m_light_list;

        ProgramShader_main m_ProgramShader_main;
        glimac::CubeGL m_cubeGL_model;


        Textures m_textures;
        GLuint m_vao;
        Game(std::string const& currentDir, bool test=false);
        ~Game();
        void initScene(Level const& level);
        void generateGridTest();

        static const int CUBEGL_VERTEX_ATTRIBUT_POSITION = 0;
        static const int CUBEGL_VERTEX_ATTRIBUT_NORMAL = 1;
        static const int CUBEGL_VERTEX_ATTRIBUT_TEXTURE = 2;
        static const int VOXEL_ATTRIBUT_POSITION = 3;
        static const int VOXEL_ATTRIBUT_TEXTURE_ID = 4;
};
