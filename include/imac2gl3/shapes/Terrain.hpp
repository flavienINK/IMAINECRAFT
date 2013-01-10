#ifndef TERRAIN_H
#define TERRAIN_H

#include <iostream>
#include <SDL/SDL_image.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "imac2gl3/shapes/GLShapeInstance.hpp"
#include "imac2gl3/shapes/CubeHerbe.hpp"
#include "imac2gl3/shapes/CubeTerre.hpp"
#include "imac2gl3/shapes/CubeEau.hpp"
#include "imac2gl3/shapes/CubeNeige.hpp"
#include "imac2gl3/shapes/CubeBois.hpp"
#include "imac2gl3/shapes/CubeRoche.hpp"
#include "imac2gl3/shapes/CubeSkybox.hpp"
#include "imac2gl3/shapes/MatrixStack.hpp"
#include "imac2gl3/Random.hpp"
#include "imac2gl3/FileOpener.hpp"
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
			CubeTerre myCubeTerre;
			CubeHerbe myCubeHerbe;
			CubeEau myCubeEau;
			/*CubeRoche myCubeRoche;
			CubeNeige myCubeNeige;*/
			CubeBois myCubeBois;
			CubeSkybox mySkybox;
			TerrainData terrain;
			GLuint program;

		public: 
			Terrain();
			
			void afficherTerrain();
			void save(glm::vec3) const;
			void load(std::string nom);
			float loadPositionCam(std::string nom, char position3D);
			void draw(MatrixStack &mstack, glm::vec3 position, int profondeur);
			
			void make(int height, int width, int x, int y, int sol, int id_Tex);			
			void blockRemove(int height, int width, int x, int y, int sol);
			
			bool addBlock(int x, int y, int z);
			bool deleteBlock(int x, int y, int z);
						
			bool blocDestructable(int i, int j, int k) const;			
			bool hasFreeSurface(int i, int j, int k) const;
			int getSolCoordonnee(glm::vec3 position) const;
			int getNearestCollisionX(glm::vec3 position) const;
			int getNearestCollisionY(glm::vec3 position) const;
	};
}

#endif
