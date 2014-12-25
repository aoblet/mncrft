#include "ProgramShader_main.hpp"
#include <iostream>

ProgramShader_main::ProgramShader_main(const std::string &currentDirectory, const std::string &nameShader){
    glimac::FilePath applicationPath(currentDirectory);

    m_program = glimac::loadProgram(applicationPath.dirPath() + "/shaders/"+ (nameShader+".vs.glsl"),
                                    applicationPath.dirPath() + "/shaders/"+ (nameShader+".fs.glsl"));

    m_uMVPMatrix = glGetUniformLocation(m_program.getGLId(), "uMVPMatrix");
    m_uMVMatrix =  glGetUniformLocation(m_program.getGLId(), "uMVMatrix");
    m_uNormalMatrix = glGetUniformLocation(m_program.getGLId(), "uNormalMatrix");
}
