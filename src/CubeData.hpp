#pragma once
#include <iostream>
#include <glimac/glm.hpp>

class CubeData{

	public:
        //CubeData();
        virtual ~CubeData(){}

        virtual glm::vec3 position() const = 0;
		virtual int durability() const;
		virtual int life() const;
		//CubeData loot() const;

		virtual void setPosition(glm::vec3 pos);
        virtual void setLife(int damage);

    protected:

		glm::vec3 m_position;
		int m_durability;
		int m_life;
		bool m_gravity;
		//CubeData *m_loot;
};
