#pragma once
#include <string>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

struct ProgramShader_main{
    GLint m_uMVPMatrix;
    GLint m_uMVMatrix;
    GLint m_uNormalMatrix;
    glimac::Program m_program;

    ProgramShader_main(std::string const& currentDirectory, std::string const& nameShader);
};
