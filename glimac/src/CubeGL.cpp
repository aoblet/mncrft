#include "glimac/CubeGL.hpp"
#include "glimac/glm.hpp"
namespace glimac{
    const ShapeVertex* CubeGL::getDataPointer() const{
        return &(m_vertices[0]);
    }

    GLsizei CubeGL::sizeVertices() const{
        return m_size_vertices;
    }

    void CubeGL::addTriangle(const glm::vec3 &first_position, const glm::vec3 &switch_position1, const glm::vec3 &switch_position2,
                             const glm::vec3 &third_position,const glm::vec3 &normal, glm::vec2* texCoords){

        m_vertices.push_back(ShapeVertex(first_position , normal, texCoords[0]));
        m_vertices.push_back(ShapeVertex(switch_position1,normal, texCoords[1]));
        m_vertices.push_back(ShapeVertex(third_position , normal, texCoords[2]));

        texCoords[1].x += 1./6; //step offset switch_coord
        texCoords[1].y += 1;
        m_vertices.push_back(ShapeVertex(first_position , normal, texCoords[0]));
        m_vertices.push_back(ShapeVertex(switch_position2,normal, texCoords[1]));
        m_vertices.push_back(ShapeVertex(third_position , normal, texCoords[2]));

        texCoords[0].x += 1./6; texCoords[2].x += 1./6; //step offset first & thrid coord
        texCoords[1].y = 0; //reset y of swith_coord
    }

    CubeGL::CubeGL():m_size_vertices(0){
        glm::vec3 first_position, switch_position1, switch_position2, third_position, normal;
        glm::vec2 texCoords[]= {glm::vec2(0,1./6), glm::vec2(0,0), glm::vec2(1./6,0)}; //0=firstPoint, 1=swithPoint, 2=thirdPoint
        //texCoords modified at each call of addTriangle

        //face 1
        first_position   = glm::vec3(-0.5,-0.5,0.5);
        switch_position1 = glm::vec3(-0.5,0.5,0.5);
        switch_position2 = glm::vec3(0.5,-0.5,0.5);
        third_position   = glm::vec3(0.5,0.5,0.5);
        normal           = glm::vec3(0,0,1);
        this->addTriangle(first_position, switch_position1, switch_position2, third_position, normal,texCoords);

        //face 2
        first_position   = glm::vec3(0.5,-0.5,0.5);
        switch_position1 = glm::vec3(0.5,0.5,0.5);
        switch_position2 = glm::vec3(0.5,-0.5,-0.5);
        third_position   = glm::vec3(0.5,0.5,-0.5);
        normal           = glm::vec3(1,0,0);
        this->addTriangle(first_position, switch_position1, switch_position2, third_position, normal,texCoords);

        //face 3
        first_position   = glm::vec3(0.5,-0.5,-0.5);
        switch_position1 = glm::vec3(0.5,0.5,-0.5);
        switch_position2 = glm::vec3(-0.5,-0.5,-0.5);
        third_position   = glm::vec3(-0.5,0.5,-0.5);
        normal           = glm::vec3(0,0,-1);
        this->addTriangle(first_position, switch_position1, switch_position2, third_position, normal,texCoords);

        //face 4
        first_position   = glm::vec3(-0.5,-0.5,-0.5);
        switch_position1 = glm::vec3(-0.5,0.5,-0.5);
        switch_position2 = glm::vec3(-0.5,-0.5,0.5);
        third_position   = glm::vec3(-0.5,0.5,0.5);
        normal           = glm::vec3(-1,0,0);
        this->addTriangle(first_position, switch_position1, switch_position2, third_position, normal,texCoords);

        //face 5
        first_position   = glm::vec3(-0.5,0.5,0.5);
        switch_position1 = glm::vec3(-0.5,0.5,-0.5);
        switch_position2 = glm::vec3(0.5,0.5,0.5);
        third_position   = glm::vec3(0.5,0.5,-0.5);
        normal           = glm::vec3(0,1,0);
        this->addTriangle(first_position, switch_position1, switch_position2, third_position, normal,texCoords);

        //face 6
        first_position   = glm::vec3(-0.5,-0.5,-0.5);
        switch_position1 = glm::vec3(-0.5,-0.5,0.5);
        switch_position2 = glm::vec3(0.5,-0.5,-0.5);
        third_position   = glm::vec3(0.5,-0.5,0.5);
        normal           = glm::vec3(0,-1,0);
        this->addTriangle(first_position, switch_position1, switch_position2, third_position, normal,texCoords);

        //update size of vertices
        m_size_vertices = m_vertices.size();
    }
}
