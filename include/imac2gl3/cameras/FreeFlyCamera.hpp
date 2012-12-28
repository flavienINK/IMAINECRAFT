#ifndef FREEFLYCAMERA_H
#define FREEFLYCAMERA_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imac2gl3/shapes/Terrain.hpp"
#include "imac2gl3/frameClocker.hpp"
#include "imac2gl3/settings.hpp"

typedef struct Jump{
	bool active;
	int start;
	int end;
}Jump;

namespace imac2gl3 {
	class FreeFlyCamera {
		private:
			glm::vec3 m_fPosition; 
			float m_fPhi;
			float m_fTheta;
			glm::vec3 m_FrontVector;
			glm::vec3 m_LeftVector;
			glm::vec3 m_UpVector;
			
			Terrain *terrain;
			bool contactSol;
			Jump  m_jump;

		public: 
			FreeFlyCamera(const glm::vec3 &startPosition, Terrain *_terrain):m_fPosition(startPosition), m_fPhi(PI), m_fTheta(-PI/2), terrain(_terrain) { m_jump.active = false; contactSol = false; computeDirectionVectors(); };
			
			void moveFront(float t);
			void moveLeft(float t);
			void moveUp(float t);
			void jumpLaunch(float time);
			
			void rotateLeft(float degrees);
			void rotateUp(float degrees);
			
			glm::mat4 getViewMatrix();
			void computeDirectionVectors();
			
			void limiteTerrain();
			void detectionSol();
			void detectionCollision();
			
			void afficherCam(){std::cout<<"position : x :"<<m_fPosition.x<<" y : "<<m_fPosition.y<<" z : "<<m_fPosition.z<<std::endl<<"frontVector : ("<<m_FrontVector.x<<", "<<m_FrontVector.y<<", "<<m_FrontVector.z<<")"<<std::endl<<"upVector : ("<<m_UpVector.x<<", "<<m_UpVector.y<<", "<<m_UpVector.z<<")"<<std::endl<<"(Teta, phi) : ("<<m_fTheta<<", "<<m_fPhi<<")"<<std::endl;};
			
	};
}

#endif
