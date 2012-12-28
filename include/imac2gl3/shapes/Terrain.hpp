#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "imac2gl3/shapes/GLShapeInstance.hpp"
#include "imac2gl3/shapes/Cube1.hpp"
#include "imac2gl3/shapes/Cube2.hpp"
#include "imac2gl3/shapes/MatrixStack.hpp"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "imac2gl3/settings.hpp"


namespace imac2gl3 {
	class Terrain {
		private:
			Cube1 myCube1;
			Cube2 myCube2;
			int terrain[LONGUEUR_TERRRAIN][LARGEUR_TERRRAIN][HAUTEUR_TERRRAIN];
			GLuint program;
			time_t seconds;

		public: 
			Terrain();
			
			void afficherTerrain();
			void save();
			void draw(MatrixStack &mstack);
			
			void moutain(int height, int width, int x, int y, int sol);
			
			int getSolCoordonnee(glm::vec3 position);
			int getNearestCollisionX(glm::vec3 position);
			int getNearestCollisionY(glm::vec3 position);
			
			bool randomBool(int balance);
			int randomPosition(char vecteur);
			int randomBalance(int balance);
			
			float random(int min, int max);
	};
}

#endif
