#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <iostream>
#include <cmath>

using namespace glimac;

struct Vertex2DUV {
  glm::vec2 position;
  glm::vec2 texture;

  Vertex2DUV(){}

  Vertex2DUV(glm::vec2 position, glm::vec2 texture):
    position(position), texture(texture) {}
};

glm::mat3 translate(float tx, float ty) {
  return glm::mat3(
    glm::vec3(1, 0, 0),
    glm::vec3(0, 1, 0),
    glm::vec3(tx, ty, 1)
  );
};

glm::mat3 scale(float sx, float sy) {
  return glm::mat3(
    glm::vec3(sx, 0, 0),
    glm::vec3(0, sy, 0),
    glm::vec3(0, 0, 1)
  );
};

glm::mat3 rotate(float degree) {
  float radian = degree * (3.14/180);
  return glm::mat3(
    glm::vec3(cos(radian) , sin(radian), 0),
    glm::vec3(-sin(radian), cos(radian), 0),
    glm::vec3(0, 0, 1)
  );
};

int main(int argc, char** argv) {
  // Initialize SDL and open a window
  SDLWindowManager windowManager(600, 600, "GLImac");

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
  Program program = loadProgram(
    applicationPath.dirPath() + "shaders/multiple_matrix.vs.glsl",
    applicationPath.dirPath() + "shaders/multiple_matrix.fs.glsl"
  );
  program.use();

  GLint vs_matrix_transform = glGetUniformLocation(program.getGLId(), "uModelMatrix");
  GLint fs_vec_color = glGetUniformLocation(program.getGLId(), "uColor");


  // vbo stuff
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  Vertex2DUV vertices[] = {
    Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 0)),
    Vertex2DUV(glm::vec2( 1, -1), glm::vec2(0, 0)),
    Vertex2DUV(glm::vec2( 0,  1), glm::vec2(0, 0))
  };
  glBufferData(
    GL_ARRAY_BUFFER,
    3 * sizeof(Vertex2DUV),
    vertices,
    GL_STATIC_DRAW
  );
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // vao stuff
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  const GLuint VERTEX_ATTR_POSITION = 0;
  const GLuint VERTEX_ATTR_TEXTURE = 1;

  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glVertexAttribPointer(
    VERTEX_ATTR_POSITION,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex2DUV),
    (GLvoid*) offsetof(Vertex2DUV, position)
  );

  glVertexAttribPointer(
    VERTEX_ATTR_TEXTURE,
    2,
    GL_FLOAT,
    GL_FALSE,
    sizeof(Vertex2DUV),
    (GLvoid*) offsetof(Vertex2DUV, texture)
  );


  // Setup instance rendering
  const GLuint TRIANGLE_POSITION_loc = 2;

  glm::vec3 positions[] = {
    glm::vec3(-0.5, 0, 0),
    glm::vec3(0.5, 0, 0)
  };

  // Create buffer
  GLuint position_buffer;
  glGenBuffers(1, &position_buffer);

  // Binding buffer
  glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
  // Describing buffer
  glVertexAttribPointer(
    TRIANGLE_POSITION_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(TRIANGLE_POSITION_loc);
  // This is the important bit... set the divisor for the color array
  // to 1 to get OpenGL to give us a new value of "color" per-instance
  // rather than per-vertex.
  glVertexAttribDivisor(TRIANGLE_POSITION_loc, 1);


//     glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Application loop:
  bool done = false;
  float rotation_clockwise = 0;
  float rotation_clockwise1 = 0;
  float rotation_counterclockwise = 0;

  glm::mat3 matrix_transform, matrix_transform1, matrix_scale;
  glm::vec3 vec_color;
  matrix_scale = scale(.25, .25);

  while(!done) {
    // Event loop:
    SDL_Event e;
    while(windowManager.pollEvent(e)) {
      if(e.type == SDL_QUIT) {
        done = true; // Leave the loop after this iteration
      }
    }

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/


    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 2, positions, GL_DYNAMIC_DRAW);

    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 2);
    glBindVertexArray(0);

    // Update the display
    windowManager.swapBuffers();
  }

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  return EXIT_SUCCESS;
}
