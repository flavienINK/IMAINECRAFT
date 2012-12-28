#include "imac2gl3/cameras/FreeFlyCamera.hpp"

namespace imac2gl3 {

	void FreeFlyCamera::moveFront(float t){
		m_fPosition.x += t * m_FrontVector.x;
		m_fPosition.z += t * m_FrontVector.z;
		detectionCollision();
	}

	void FreeFlyCamera::moveLeft(float t){
		m_fPosition += t * m_LeftVector;
		detectionCollision();
	}
	
	void FreeFlyCamera::moveUp(float t){
		m_fPosition.y += t ;
		detectionSol();
		detectionCollision();
	}
	
	void FreeFlyCamera::jumpLaunch(float time){
		if( contactSol ){
				contactSol = false;
				m_jump.active=true;
				m_jump.start = SDL_GetTicks();
				m_jump.end = m_jump.start + time * 1000;
		}
	}	
	
	void FreeFlyCamera::detectionSol(){
		int solCoord = terrain->getSolCoordonnee(m_fPosition);
		if( m_fPosition.y < solCoord && m_fPosition.y + 1 > solCoord )
		 {m_fPosition.y = solCoord; contactSol = true;}
	}
	
	void FreeFlyCamera::detectionCollision(){
		int XNearestCollision = terrain->getNearestCollisionX(m_fPosition);
		int YNearestCollision = terrain->getNearestCollisionY(m_fPosition);
		
		if( m_fPosition.x < XNearestCollision && (XNearestCollision - m_fPosition.x <= 1.9*SPEED_DEPLACEMENT)){
			m_fPosition.x = XNearestCollision - 2*SPEED_DEPLACEMENT;
			std::cout<<"COLL1 : "<<"XnearestCol => "<<XNearestCollision<<" XPosition =>"<<m_fPosition.x<<std::endl;
		}
		if( m_fPosition.x > XNearestCollision && (m_fPosition.x - XNearestCollision <= 1.9*SPEED_DEPLACEMENT)){
			m_fPosition.x = XNearestCollision + 2*SPEED_DEPLACEMENT;
			std::cout<<"COLL2"<<std::endl;

		}
		
		if( -m_fPosition.z < YNearestCollision && (YNearestCollision - (-m_fPosition.z) <= 1.9*SPEED_DEPLACEMENT)){
			m_fPosition.z = - (YNearestCollision - 2*SPEED_DEPLACEMENT);
			std::cout<<"COLL3 : "<<"YnearestCol => "<<YNearestCollision<<" YPosition =>"<<-m_fPosition.z<<std::endl;


		}
		if( -m_fPosition.z > YNearestCollision && ( (-m_fPosition.z) - YNearestCollision <= 1.9*SPEED_DEPLACEMENT)){
			m_fPosition.z = - (YNearestCollision + 2*SPEED_DEPLACEMENT);
			std::cout<<"COLL4"<<std::endl;

		}
	}
	
	void FreeFlyCamera::rotateLeft(float degrees){
		m_fPhi += PI * degrees / 180;
		computeDirectionVectors();
	}

	void FreeFlyCamera::rotateUp(float degrees){
		m_fTheta += PI * degrees / 180;
		if( m_fTheta > PI/2 ) m_fTheta = PI/2;
		if( m_fTheta < -PI/2 ) m_fTheta = -PI/2;
		computeDirectionVectors();
	}

	glm::mat4 FreeFlyCamera::getViewMatrix(){
		// Detection saut actif
		if( m_jump.active ) moveUp(SPEED_DEPLACEMENT * 1.5);
		if ( SDL_GetTicks() > m_jump.end ) m_jump.active=false;
		
		//detectionSol();
		//detectionCollision();
		
		// Retourne la matrice View
		glm::mat4 V = glm::lookAt(glm::vec3(m_fPosition.x, m_fPosition.y, m_fPosition.z), glm::vec3(m_fPosition.x, m_fPosition.y, m_fPosition.z) + m_FrontVector, m_UpVector);
		return V;
	}

	void FreeFlyCamera::computeDirectionVectors(){
		m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
		m_LeftVector = glm::vec3(sin(m_fPhi + PI/2), 0, cos(m_fPhi + PI/2));
		m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
	}

}

