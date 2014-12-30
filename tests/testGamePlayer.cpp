#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/CubeGL.hpp>
#include <glimac/FreeFlyCamera.hpp>
#include <vector>
#include "Textures.hpp"
#include "CubeDirt.hpp"
#include "CubeSand.hpp"
#include "Game.hpp"
#include "Level.hpp"

using namespace glimac;

// desired framerate in milliseconds
static const Uint32 FRAMERATE = 1000 / 60;

int main(int argc, char** argv) {
    const int WIDTH = 800;
    const int HEIGHT = 600;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WIDTH, HEIGHT, "testGamePlayer");
    SDL_ShowCursor(0);
    SDL_WM_GrabInput( SDL_GRAB_ON );

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        throw std::logic_error("Error glew setup");
    }

    bool TEST = false;
    Game game(argv[0],"../../tests/outputJson/game.json","../../tests/outputJson/game.json",TEST);
    game.m_ProgramShader_main.m_program.use();

    Player& player1 = game.m_player;

    glm::mat4 matrixView(player1.camera().getViewMatrix());
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 250.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1),glm::vec3(0,0,-5));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(game.m_vao_cubeData);
    glBindTexture(GL_TEXTURE_2D_ARRAY, game.m_textures.idTexture());

    //faster (test)
    int sizeCube = game.m_cube_list.size();
    int sizeCubeGL = game.m_cubeGL_model.sizeVertices();

    Uint32 startTime;
    Uint32 elapsedTime;
    glm::ivec2 mouseCurrenPosition;

    bool done = false;
    while(!done) {

        startTime = SDL_GetTicks();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                done = true; // Leave the loop after this iteration
            }
        }

        player1.handleMove(windowManager);

        mouseCurrenPosition = windowManager.getMouseMotionRelative();
        player1.m_camera.rotateLeft(-(mouseCurrenPosition.x)/2.);
        player1.m_camera.rotateUp(-( mouseCurrenPosition.y)/2.);


        matrixView = player1.camera().getViewMatrix();
        MVMatrix = matrixView ;
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(game.m_ProgramShader_main.m_uMVPMatrix, 1,GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
        glUniformMatrix4fv(game.m_ProgramShader_main.m_uNormalMatrix, 1,GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(game.m_ProgramShader_main.m_uMVMatrix,1,GL_FALSE, glm::value_ptr(MVMatrix));

        glClearColor(0.45,0.6,0.9,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArraysInstanced(GL_TRIANGLES, 0, sizeCubeGL, sizeCube);

        // Update the display
        windowManager.swapBuffers();

        // calculating elapsed time && wait if necessary
        elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE) {
          SDL_Delay(FRAMERATE - elapsedTime);
        }
    }

    return EXIT_SUCCESS;
}
