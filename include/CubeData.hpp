#pragma once
#include "Textures.hpp"
#include <glimac/glm.hpp>
#include <GL/gl.h>

class CubeData{
    private:
        int m_life;
        bool m_gravity;
        const int m_durability;
        int computeCurrentLevel_texture() const;

	public:
        int m_currentLevel_texture; //texture stuff in public => vao offsetof
        GLint m_idTexture;
        glm::vec3 m_position;

        CubeData(glm::vec3 const& position, bool gravity, int life, GLint idTexture, int durability);
        ~CubeData();

        glm::vec3 position() const;
        int durability() const;
        float life() const;
        GLint idTexture() const;
        int currentLevel_texture() const;

        void setPosition(glm::vec3 const& pos);
        void inflictDamage(float damage);
        void setIdTexture(GLint newId);
};
