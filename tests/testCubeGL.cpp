#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/CubeGL.hpp>
#include <glimac/FreeFlyCamera.hpp>

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

struct Vertex {
    glm::vec2 position;
    glm::vec2 texCoords;
};



int main(int argc, char** argv) {
    const int WIDTH = 800;
    const int HEIGHT = 600;
    // Initialize SDL and open a window
    SDLWindowManager windowManager(WIDTH, HEIGHT, "cubeData");

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

    GLint uTexture = glGetUniformLocation(program.getGLId(), "uTexture");
    glUniform1i(uTexture, 0);

    auto pImg = loadImage(applicationPath.dirPath() + "/assets/textures/triforce2.png");
    if(!pImg) {
        std::cerr << "Unable to load the texture" << std::endl;
        return EXIT_FAILURE;
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pImg->getWidth(), pImg->getHeight(), 0, GL_RGBA, GL_FLOAT, pImg->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    std::cout << uMVPMatrix << std::endl;

    CubeGL cube;
    GLuint vbo, vao;

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    Vertex triangle[] = {
        { glm::vec2(-1, -1), glm::vec2(0, 1) },
        { glm::vec2(1, -1), glm::vec2(1, 1) },
        { glm::vec2(0, 1), glm::vec2(0.5, 0) }
    };


    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, cube.sizeVertices()*sizeof(ShapeVertex), cube.getDataPointer(), GL_STATIC_DRAW);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));

    glEnable(GL_DEPTH_TEST);
    // Application loop:
    FreeFlyCamera freeCamera(0,0,10);

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
        glDrawArrays(GL_TRIANGLES, 0, cube.sizeVertices());

        // Update the display
        windowManager.swapBuffers();
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
