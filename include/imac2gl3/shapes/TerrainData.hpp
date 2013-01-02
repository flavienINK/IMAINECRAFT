#ifndef TERRAINDATA_H
#define TERRAINDATA_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "imac2gl3/settings.hpp"


namespace imac2gl3 {
	class TerrainData {
		private:
			int taille;
			std::vector<int> data;

		public: 
			TerrainData(): taille(LONGUEUR_TERRRAIN*LARGEUR_TERRRAIN*HAUTEUR_TERRRAIN) {data.resize(taille);std::cout<<"taille :"<<taille<<std::endl; };
			
			int& operator()(int i, int j, int k){ return data[i*( LARGEUR_TERRRAIN * HAUTEUR_TERRRAIN ) + j*HAUTEUR_TERRRAIN + k];}
			
	};
}

#endif
