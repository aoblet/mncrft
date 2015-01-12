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
#include "CubeFoundation.hpp"
#include "CubeRock.hpp"
#include "PerlinNoise.hpp"

using namespace glimac;

// desired framerate in milliseconds
static const Uint32 FRAMERATE = 1000 / Game::FRAME_PER_SECOND;

int main(int argc, char** argv) {
    int WIDTH = 1350;
    int HEIGHT = 750;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(WIDTH, HEIGHT, "Minecraft 3000");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        throw std::logic_error("Error glew setup");
    }

    /**** INIT GAME ****/
    std::string level = argc >1 && std::string(argv[1]).find("perfo") != std::string::npos ? "perfo" : "game";
    std::cout << argv[1] << std::endl;
    Game::createSingleton(argv[0],"../../game_save/"+level+".json","../../game_save/"+level+".json");
    Skybox skybox(argv[0], "cubeMap",*Game::singletonGame());
    Player& player1 = Game::singletonGame()->player();
    /******************/

    std::cout << Game::singletonGame()->m_cube_list.size() << " cubes" << std::endl;

    glm::mat4 matrixView(player1.camera().getViewMatrix());
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 1000.f);

    Uint32 startTime;
    Uint32 elapsedTime;

    glEnable(GL_DEPTH_TEST);
    glBindBuffer(GL_UNIFORM_BUFFER, Game::singletonGame()->m_ProgramShader_main.m_ubo_matricesGlobales);
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
                ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 1000.f);
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));

            }

            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_o)
                windowManager.toogleCursorMode();

            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b){
                ProjMatrix = glm::perspective(glm::radians(120.f),(float)(WIDTH)/HEIGHT ,0.1f, 1000.f);
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));
            }

            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n){
                ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 1000.f);
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4)*2, sizeof(glm::mat4), glm::value_ptr(ProjMatrix));
            }
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_t){
                Game::singletonGame()->textures().changeUniverse();
                skybox.changeUniverse();
            }
        }

        player1.handleMove(windowManager);
        player1.gameInteraction().handleInteraction(windowManager);

        matrixView = player1.camera().getViewMatrix();
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(ProjMatrix*matrixView)); //mvp
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(matrixView));//view
        glUniform3fv(Game::singletonGame()->m_ProgramShader_main.m_uLights,CubeLight::MAX_LIGHT,&(Game::singletonGame()->m_uLightsArray[0][0]));


        glClearColor(0.45,0.6,0.9,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        skybox.renderSkybox();
        Game::singletonGame()->renderGame();

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
