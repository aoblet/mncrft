#pragma once
#include <string>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

struct ProgramShader_main{
    GLint m_uMVPMatrix;
    GLint m_uViewMatrix;
    GLint m_uLights;
    GLuint m_ubo_matricesGlobales;
    GLuint m_globalUniformBlockIndex;

    glimac::Program m_program;

    ProgramShader_main(std::string const& currentDirectory, std::string const& nameShader);
    ~ProgramShader_main();
};
