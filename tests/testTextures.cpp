#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include "Textures.hpp"
using namespace glimac;
int main(int argc, char** argv) {
    SDLWindowManager windowManager(800, 600, "triforce");

    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    bool setUpTextureForGame = false;
    Textures texture(setUpTextureForGame);
    texture.setUpTexturesTEST(
      "assets/textures/dust.png",
      "assets/textures/dirt.png"
    );



    return 0;
}
