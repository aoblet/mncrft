#pragma once
#include <iostream>
#include <glimac/glm.hpp>
#include <GL/gl.h>

class CubeData{

    protected:
        glm::vec3 m_position;
        int m_life;
        bool m_gravity;
        GLint m_idTexture;
        //CubeData *m_loot;

	public:
        CubeData(glm::vec3 position, bool gravity, int life ,GLint idTexture);
        virtual ~CubeData(){}

        virtual glm::vec3 position() const;
        virtual int durability() const = 0;
		virtual int life() const;
        virtual GLint idTexture() const;

		virtual void setPosition(glm::vec3 pos);
        virtual void setLife(int damage);
        virtual void setIdTexture(GLint newId);
};
