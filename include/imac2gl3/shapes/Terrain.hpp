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
#include "imac2gl3/Random.hpp"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <sstream>

#include "imac2gl3/settings.hpp"
#include "imac2gl3/shapes/TerrainData.hpp"

namespace imac2gl3 {
	class Terrain{
		private:
			Cube1 myCube1;
			Cube2 myCube2;
			TerrainData terrain;
			GLuint program;

		public: 
			Terrain();
			
			void afficherTerrain();
			void save(glm::vec3);
			void load(std::string nom);
			float loadPositionCam(std::string nom, char position3D);
			void draw(MatrixStack &mstack, glm::vec3 position, int profondeur);
			
			void relief(int height, int width, int x, int y, int sol);
			void pyramid(int height, int width, int x, int y, int sol);
			void cavity(int height, int width, int x, int y, int z);
			void water(int length, int width, int x, int y, int sol);
			
			void blockRemove(int height, int width, int x, int y, int sol);
			
			void addBlock(int x, int y, int z);
			void deleteBlock(int x, int y, int z);
						
			bool hasFreeSurface(int i, int j, int k);
			int getSolCoordonnee(glm::vec3 position);
			int getNearestCollisionX(glm::vec3 position);
			int getNearestCollisionY(glm::vec3 position);
	};
}

#endif
