#pragma once
#include <glimac/glm.hpp>
#include <GL/gl.h>

class CubeData{
    protected:
        static const int maxLevels_texture = 6;

        int m_life;
        glm::vec3 m_position;
        bool m_gravity;
        int computeCurrentLevel_texture() const;

	public:
        int m_currentLevel_texture; //texture stuff in public => vao offsetof
        GLint m_idTexture;

        CubeData(glm::vec3 const& position, bool gravity, int life, GLint idTexture);
        virtual ~CubeData();

        virtual glm::vec3 position() const;
        virtual int durability() const = 0;
        virtual float life() const;
        virtual GLint idTexture() const;
        virtual int currentLevel_texture() const;

        virtual void setPosition(glm::vec3 const& pos);
        virtual void inflictDamage(float damage);
        virtual void setIdTexture(GLint newId);
};
