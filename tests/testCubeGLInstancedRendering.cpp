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

using namespace glimac;

/*********************************
 *
 * Ce fichier est un exemple d'application minimale utilisant shaders et textures
 * Le but est pour vous de comprendre quel chemin de fichier utiliser pour charger vos shaders et assets
 *
 * Au moment de la compilation, tous les shaders (.glsl) du repertoire du même nom sont copiés dans le repertoire
 * "shaders" à coté de l'executable. Ainsi pour obtenir le chemin vers le shader "tex2D.vs.glsl", on utilise
 * le chemin vers notre executable, contenu dans argv[0]:
 *
 * FilePath applicationPath(argv[0]);
 *
 * Le chemin du shader à charger est alors: applicationPath.dirPath() + "/shaders/tex2D.vs.glsl"
 *
 * De la même manière, tous les fichiers (sans contrainte d'extension) du repertoire assets sont copiés dans
 * le repertoire "assets" à coté de l'executable. Pour obtenir le chemin vers la texture "textures/triforce.png" on fait:
 *
 * applicationPath.dirPath() + "/assets/textures/triforce.png"
 *
 * easy peasy.
 *
 *********************************/




int main(int argc, char** argv) {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WIDTH, HEIGHT, "cubeData Instanced Rendering");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "/shaders/tex3D.vs.glsl",
                                  applicationPath.dirPath() + "/shaders/tex3D.fs.glsl");
    program.use();


    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    CubeGL cube;
    GLuint vbo, vao;

    cube.generateVbo(&vbo);
    cube.generateVao(&vao, vbo, 0, 1, 2);

    CubeDirt cubeDirt(
      glm::vec3(0, 0, 0),
      0
    );

    CubeSand cubeSand(
      glm::vec3(0, 1, 0),
      1
    );

    // Cube positions for instanced rendering
    // Setup instance rendering
    const GLuint CUBE_POSITION_loc = 3;

    // Fake cube positions
    std::vector<glm::vec3> cubePositions = {
      cubeDirt.position(),
      cubeSand.position()
    };

    // Create position buffer
    GLuint cubePosition_buffer;
    glGenBuffers(1, &cubePosition_buffer);

    glBindVertexArray(vao); // do not forget to bind a vao

    // Binding buffer
    glBindBuffer(GL_ARRAY_BUFFER, cubePosition_buffer);
    glEnableVertexAttribArray(CUBE_POSITION_loc);

    // Describing data
    glVertexAttribPointer(
      CUBE_POSITION_loc,
      3,
      GL_FLOAT,
      GL_FALSE,
      sizeof(glm::vec3),
      NULL
    );

    // Binding data
    glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(glm::vec3) * cubePositions.size(),
      &cubePositions[0],
      GL_DYNAMIC_DRAW
    );

    // Iterate for each instance (instanced rendering stuff)
    glVertexAttribDivisor(CUBE_POSITION_loc, 1);
    glBindVertexArray(0);



    const GLuint CUBE_TEXTURE_ID_loc = 4;
    std::vector<int> cubeTextureIds = {
      cubeDirt.idTexture(),
      cubeSand.idTexture()
    };
    // Create textureId buffer
    GLuint cubeTextureId_buffer;
    glGenBuffers(1, &cubeTextureId_buffer);

    glBindVertexArray(vao); // do not forget to bind a vao

    // Binding buffer
    glBindBuffer(GL_ARRAY_BUFFER, cubeTextureId_buffer);
    glEnableVertexAttribArray(CUBE_TEXTURE_ID_loc);

    // Describing data
    glVertexAttribPointer(
      CUBE_TEXTURE_ID_loc,
      1,
      GL_FLOAT,
      GL_FALSE,
      sizeof(int),
      NULL
    );

    // Binding data
    glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(int) * cubeTextureIds.size(),
      &cubeTextureIds[0],
      GL_DYNAMIC_DRAW
    );

    // Iterate for each instance (instanced rendering stuff)
    glVertexAttribDivisor(CUBE_TEXTURE_ID_loc, 1);
    glBindVertexArray(0);


    // Texture stuff
    Textures textures(false);
    textures.setUpTexturesTEST(
      "assets/textures/dust.png",
      "assets/textures/dirt.png"
    );

    glEnable(GL_DEPTH_TEST);

    // Application loop:
    FreeFlyCamera freeCamera(0,0,5);

    glm::mat4 matrixView(freeCamera.getViewMatrix());
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f),(float)(WIDTH)/HEIGHT ,0.1f, 250.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1),glm::vec3(0,0,-5));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glm::ivec2 previousMousePosition= glm::ivec2(0,0);
    double speedMoveKey = 0.001;
    // Application loop:
    bool done = false;
    while(!done) {
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
        MVMatrix = matrixView ;
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

        glUniformMatrix4fv(uMVPMatrix, 1,GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1,GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uMVMatrix,1,GL_FALSE, glm::value_ptr(MVMatrix));

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glBindTexture(GL_TEXTURE_2D_ARRAY, textures.idTexture());

        glBindVertexArray(vao);

        glDrawArraysInstanced(GL_TRIANGLES, 0, cube.sizeVertices(), 2);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
