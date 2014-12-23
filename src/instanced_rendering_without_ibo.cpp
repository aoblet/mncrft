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
    glm::vec3(0, 0, 1));
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
    Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)),
    Vertex2DUV(glm::vec2( 1, -1), glm::vec2(1, 1)),
    Vertex2DUV(glm::vec2( 0,  1), glm::vec2(.5, 0))
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
    glm::vec3(0, 1, 0),
    glm::vec3(1, 0, 0)
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


  // Create buffer
  const GLuint scale_loc = 3;
  glm::mat3 scale_matrix = scale(.5, .5);
  std::cout << scale_matrix << std::endl;

  GLuint scale_matrix_buffer;

  glGenBuffers(1, &scale_matrix_buffer);
  // Likewise, we can do the same with the model matrix. Note that a
  // matrix input to the vertex shader consumes N consecutive input
  // locations, where N is the number of columns in the matrix. So...
  // we have four vertex attributes to set up.
  glBindBuffer(GL_ARRAY_BUFFER, scale_matrix_buffer);
  // Loop over each column of the matrix...
 for (int i = 0; i < 4; i++) {
   // Set up the vertex attribute
   glVertexAttribPointer(scale_loc + i,              // Location
                         4, GL_FLOAT, GL_FALSE,       // vec4
                         sizeof(glm::mat4),                // Stride
                         (void *)(sizeof(glm::vec4) * i)); // Start offset
   // Enable it
   glEnableVertexAttribArray(scale_loc + i);
   // Make it instanced
   glVertexAttribDivisor(scale_loc + i, 1);
 }

 glBindVertexArray(0);




 // Texture stuff

 std::unique_ptr<Image> texture_img = loadImage("/home/mathias/Dropbox/IMAC-Mathias/a2/synthese-d-image/GLImac-Template/assets/textures/triforce.png");
 if (texture_img == NULL) {
     exit(0);
 }


 GLuint texture;
 glGenTextures(1, &texture);
 glBindTexture(GL_TEXTURE_2D, texture);
 glTexImage2D(
     GL_TEXTURE_2D,
     0,
     GL_RGBA,
     texture_img->getWidth(),
     texture_img->getHeight(),
     0,
     GL_RGBA,
     GL_FLOAT,
     texture_img->getPixels()
 );

 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 glBindTexture(GL_TEXTURE_2D, 0);






  // Application loop:
  bool done = false;
  int instanceCount = 2;

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * instanceCount, positions, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, scale_matrix_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instanceCount, &scale_matrix, GL_DYNAMIC_DRAW);

    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, instanceCount);
    glBindVertexArray(0);

    // Update the display
    windowManager.swapBuffers();
  }

  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  return EXIT_SUCCESS;
}
