#pragma once

#include "glimac/glm.hpp"
#include <ostream>

class FreeFlyCamera {
    private:
		glm::vec3 m_Position;
		float m_fPhi;
		float m_fTheta;

		/*ces variables sont redondantes puisqu'elles peuvent être calculés 
		à partir des coordonnées sphériques, mais elles nous permettront de 
		faire moins de calcul à chaque tour de boucle*/

		glm::vec3 m_FrontVector;
		glm::vec3 m_LeftVector;
		glm::vec3 m_UpVector;
        float convertDegreesToRadians(float degrees);

	public:
        FreeFlyCamera(float x =0, float y=0 ,float z=5);
		void computeDirectionVectors();
        void moveLeft(float t);
        void moveFront(float t);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        glm::mat4 getViewMatrix() const;
        friend std::ostream& operator<<(std::ostream & flux, FreeFlyCamera const& camera);
};

std::ostream& operator<<(std::ostream & flux, FreeFlyCamera const& camera);
