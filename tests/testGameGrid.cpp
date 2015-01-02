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
    SDLWindowManager windowManager(WIDTH, HEIGHT, "testGrid");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        throw std::logic_error("Error glew setup");
    }

    bool TEST = true;
    Game game(argv[0],"../../tests/outputJson/game.json","",TEST);
    game.generateGridTest();
    game.m_ProgramShader_main.m_program.use();

    glEnable(GL_DEPTH_TEST);

    FreeFlyCamera freeCamera(0,0,0);
    glm::mat4 matrixView(freeCamera.getViewMatrix());
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 250.f);

    glm::ivec2 previousMousePosition= glm::ivec2(0,0);
    double speedMoveKey = 0.01;
    // Application loop:
    glBindVertexArray(game.m_vao_cubeData);
    glBindTexture(GL_TEXTURE_2D_ARRAY, game.textures().idTexture());

    int sizeCube = game.m_cube_list.size();
    int sizeCubeGL = game.m_cubeGL_model.sizeVertices();

    Uint32 startTime;
    Uint32 elapsedTime;

    bool done = false;
    while(!done) {

        startTime = SDL_GetTicks();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT){
                    previousMousePosition = windowManager.getMousePosition();
                }
            }
        }

        if(windowManager.isKeyPressed(SDLK_z)){
            freeCamera.moveFront(speedMoveKey);
        }
        if(windowManager.isKeyPressed(SDLK_q)){
            freeCamera.moveLeft(speedMoveKey);
        }
        if(windowManager.isKeyPressed(SDLK_s)){
            freeCamera.moveFront(-speedMoveKey);
        }
        if(windowManager.isKeyPressed(SDLK_d)){
            freeCamera.moveLeft(-speedMoveKey);
        }


        if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
            glm::ivec2 mouseCurrenPosition = windowManager.getMousePosition();
            freeCamera.rotateLeft(-(mouseCurrenPosition.x -previousMousePosition.x)/2.);
            freeCamera.rotateUp(-( mouseCurrenPosition.y -previousMousePosition.y)/2.);
            previousMousePosition = mouseCurrenPosition;
        }

        matrixView = freeCamera.getViewMatrix();

        glUniformMatrix4fv(game.m_ProgramShader_main.m_uMVPMatrix, 1,GL_FALSE, glm::value_ptr(ProjMatrix*matrixView));
        glUniformMatrix4fv(game.m_ProgramShader_main.m_uNormalMatrix, 1,GL_FALSE, glm::value_ptr(matrixView));
        glUniformMatrix4fv(game.m_ProgramShader_main.m_uViewMatrix,1,GL_FALSE, glm::value_ptr(matrixView));

        glClearColor(0.45,0.6,0.9,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArraysInstanced(GL_TRIANGLES, 0, sizeCubeGL, sizeCube);

        // Update the display
        windowManager.swapBuffers();


        // calculating elapsed time
        elapsedTime = SDL_GetTicks() - startTime;
        // wait if necesssary
        if(elapsedTime < FRAMERATE) {
          SDL_Delay(FRAMERATE - elapsedTime);
        }
    }

    //Level level;
    //level.gameToJson(game,"../../tests/outputJson/game.json",true,true);
    return EXIT_SUCCESS;
}
