#pragma once
#include <string>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

struct ProgramShader_main{
    GLint m_uMVPMatrix;
    GLint m_uViewMatrix;
    GLint m_uNormalMatrix;
    GLint m_uLights;
    glimac::Program m_program;

    ProgramShader_main(std::string const& currentDirectory, std::string const& nameShader);
};
