#include "ProgramShader_main.hpp"
#include <iostream>
#include <glimac/glm.hpp>

ProgramShader_main::ProgramShader_main(const std::string &currentDirectory, const std::string &nameShader){
    glimac::FilePath applicationPath(currentDirectory);

    m_program = glimac::loadProgram(applicationPath.dirPath() + "/shaders/"+ (nameShader+".vs.glsl"),
                                    applicationPath.dirPath() + "/shaders/"+ (nameShader+".fs.glsl"));

    m_globalUniformBlockIndex = glGetUniformBlockIndex(m_program.getGLId(), "GlobalMatrices");
    glGenBuffers(1, &m_ubo_matricesGlobales);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_matricesGlobales);
    glBufferData(GL_UNIFORM_BUFFER, 3*sizeof(glm::mat4), NULL, GL_STREAM_DRAW);
    glUniformBlockBinding(m_program.getGLId(), m_globalUniformBlockIndex, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, m_ubo_matricesGlobales, 0, sizeof(glm::mat4) * 3);
    glBindBuffer(GL_UNIFORM_BUFFER,0);

    m_uLights = glGetUniformLocation(m_program.getGLId(),"uLights");
}

ProgramShader_main::~ProgramShader_main(){
    glDeleteBuffers(1,&m_ubo_matricesGlobales);
}
