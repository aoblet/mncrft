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
#include <glimac/Skybox.hpp>

using namespace glimac;

// desired framerate in milliseconds
static const Uint32 FRAMERATE = 1000 / Game::FRAME_PER_SECOND;

int main(int argc, char** argv) {
    int WIDTH = 1350;
    int HEIGHT = 750;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WIDTH, HEIGHT, "testGamePlayer");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        throw std::logic_error("Error glew setup");
    }

    bool TEST = false;
    Game game(argv[0],"../../tests/outputJson/gameCircle.json","../../tests/outputJson/gameCircle.json",TEST);
    Skybox skybox(argv[0], "cubeMap",game);


    std::cout << game.m_cube_list.size() << std::endl;
    Player& player1 = game.player();

    glm::mat4 matrixView(player1.camera().getViewMatrix());
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 250.f);

    int sizeCubeGL = game.m_cubeGL_model.sizeVertices();
    Uint32 startTime;
    Uint32 elapsedTime;
    glm::ivec2 mouseCurrenPosition;

    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(game.m_vao_cubeData);
    glBindBuffer(GL_UNIFORM_BUFFER, game.m_ProgramShader_main.m_ubo_matricesGlobales);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));

    bool done = false;
    while(!done) {
        startTime = SDL_GetTicks();

        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                done = true; // Leave the loop after this iteration
            }

            if(e.type == SDL_MOUSEBUTTONDOWN && (e.button.button == SDL_BUTTON_WHEELDOWN || e.button.button == SDL_BUTTON_WHEELUP))
                player1.gameInteraction().handleChoiceCubeType(e);
            if(e.type == SDL_RESIZABLE){
                WIDTH = e.resize.w;
                HEIGHT = e.resize.h;
                ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 250.f);
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));

            }

            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_o)
                windowManager.toogleCursorMode();

            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b){
                ProjMatrix = glm::perspective(glm::radians(120.f),(float)(WIDTH)/HEIGHT ,0.1f, 250.f);
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));
            }

            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n){
                ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 250.f);
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));
            }
        }

        //std::cout << player1.currentCubeType() << std::endl;
        player1.handleMove(windowManager);
        player1.gameInteraction().handleInteraction(windowManager);

        mouseCurrenPosition = windowManager.getMouseMotionRelative();
        player1.camera().rotateLeft(-(mouseCurrenPosition.x)/3.);
        player1.camera().rotateUp(-( mouseCurrenPosition.y)/3.);


        matrixView = player1.camera().getViewMatrix();
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(ProjMatrix*matrixView)); //mvp
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrixView));//view
        glUniform3fv(game.m_ProgramShader_main.m_uLights,CubeLight::MAX_LIGHT,&(game.m_uLightsArray[0][0]));


        glClearColor(0.45,0.6,0.9,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        skybox.renderSkybox();
        game.renderGame();

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

