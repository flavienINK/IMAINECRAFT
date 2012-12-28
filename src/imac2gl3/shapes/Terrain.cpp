#include "imac2gl3/shapes/Terrain.hpp"

using namespace std;

namespace imac2gl3 {

	Terrain::Terrain(){
		
		// Chargement des shaders
		program = loadProgram("./shaders/texture.vs.glsl",
		"./shaders/texture.fs.glsl");
		if(!program) {
			exit(EXIT_FAILURE);
		}
		glUseProgram(program);
		
		glUniform1i(glGetUniformLocation(program, "uTexture"), 0);
		
		//int coucheEpaisseur = glm::floor(0.3*HAUTEUR_TERRRAIN);
		int sol = 2; // Pour hauteur = 15
		
		
		//std::cout<<sol<<std::endl;
		// Construction du terrain entier, tout est rempli et par couche (texture cube)
		for(int i=0; i<LONGUEUR_TERRRAIN; ++i){
			for(int j=0; j<LARGEUR_TERRRAIN; ++j){
				for(int k=0; k<HAUTEUR_TERRRAIN; ++k){
					if(k==0){
						terrain[i][j][k] = 1;
					}else if(k==1){
						terrain[i][j][k] = 1;
					}else if(k==2){
						terrain[i][j][k] = 2;
					}else terrain[i][j][k] = 0;
				}	
			}
		}
		
		/* Génération de montagnes */
		for(int i = 1; i<40; ++i){
			moutain(randomBalance(7), 8, randomPosition('x'), randomPosition('y'), sol);
		}
	}
	
	void Terrain::afficherTerrain(){
		for(int i=0; i<LONGUEUR_TERRRAIN; ++i) 
		for(int j=0; j<LARGEUR_TERRRAIN; ++j)
			for(int k=0; k<HAUTEUR_TERRRAIN; ++k)
			{
				std::cout<<terrain[i][j][k];
				if(k == 9) std::cout<<std::endl;
			}
	}
	
	void Terrain::draw(MatrixStack &mstack){
		
		//Compensation taille du cube
		mstack.translate(glm::vec3(0.5, -0.5, -0.5));
		
		//Compensation taille du personnage
		mstack.translate(glm::vec3(0, -1.5, 0));
		
		GLint uMVPMatrix = glGetUniformLocation(program, "uMVPMatrix");
		
		
		{
			//Boucle concernant le cube1
			//Bind de la Texture
			GLShapeInstance cube(myCube1);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cube.getTexture());
			
				for(int i=0; i<LONGUEUR_TERRRAIN; ++i) 
					for(int j=0; j<LARGEUR_TERRRAIN; ++j)
						for(int k=0; k<HAUTEUR_TERRRAIN; ++k)
						{
							if(terrain[i][j][k] == 1){
								mstack.push();
								mstack.translate(glm::vec3(i, k, -j));
								
								//Transmission de la matrice MVP au vertex shader
								glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mstack.top()));
								
								cube.draw();
								
								mstack.pop();
							}
						}
		
					
			//Debind de la texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}		
		
		{
			//Boucle concernante le cube2	
			//Bind de la Texture
			GLShapeInstance cube(myCube2);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cube.getTexture());
		
				for(int i=0; i<LONGUEUR_TERRRAIN; ++i) 
					for(int j=0; j<LARGEUR_TERRRAIN; ++j)
						for(int k=0; k<HAUTEUR_TERRRAIN; ++k)
						{
							if(terrain[i][j][k] == 2){
								mstack.push();
								mstack.translate(glm::vec3(i, k, -j));
								
								//Transmission de la matrice MVP au vertex shader
								glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mstack.top()));
								
								cube.draw();
								
								mstack.pop();
							}
						}
					
			//Debind de la texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}
	
	void Terrain::moutain(int height, int width, int x, int y, int sol){
		int idTex = 2;
		for(int hauteur = 0; hauteur < height; ++hauteur)
		{
			for(int i = 1; i<width-hauteur; ++i)
			{
				if
				(
					x+i < LARGEUR_TERRRAIN &&
					x+i < LONGUEUR_TERRRAIN &&
					x-i < LARGEUR_TERRRAIN &&
					x-i < LONGUEUR_TERRRAIN &&
					y+i < LARGEUR_TERRRAIN &&
					y+i < LONGUEUR_TERRRAIN &&
					y-i < LARGEUR_TERRRAIN &&
					y-i < LONGUEUR_TERRRAIN
				)
				{
					if(hauteur >= 5) idTex = 1;
					/* pivot montagne */
					if(terrain[x][y][sol+1+hauteur]==0) terrain[x][y][sol+1+hauteur] = idTex;
					/* etoile */
					if(terrain[x+i][y][sol+1+hauteur]==0) terrain[x+i][y][sol+1+hauteur] = idTex;
					if(terrain[x][y+i][sol+1+hauteur]==0) terrain[x][y+i][sol+1+hauteur] = idTex;
					if(terrain[x][y-i][sol+1+hauteur]==0) terrain[x][y-i][sol+1+hauteur] = idTex;
					if(terrain[x-i][y][sol+1+hauteur]==0) terrain[x-i][y][sol+1+hauteur] = idTex;
					for(int j = 1; j<width-hauteur; j++)
					{
						if
						(
							x+i < LARGEUR_TERRRAIN &&
							x+i < LONGUEUR_TERRRAIN &&
							x-i < LARGEUR_TERRRAIN &&
							x-i < LONGUEUR_TERRRAIN &&
							y+i < LARGEUR_TERRRAIN &&
							y+i < LONGUEUR_TERRRAIN &&
							y-i < LARGEUR_TERRRAIN &&
							y-i < LONGUEUR_TERRRAIN
						)
						{
							/*zone 1*/
							if(terrain[x+i][y+j][sol+1+hauteur]==0) terrain[x+i][y+j][sol+1+hauteur] = idTex;
							/*zone 2*/
							if(terrain[x+i][y-j][sol+1+hauteur]==0) terrain[x+i][y-j][sol+1+hauteur] = idTex;
							/*zone 3*/
							if(terrain[x-i][y+j][sol+1+hauteur]==0) terrain[x-i][y+j][sol+1+hauteur] = idTex;
							/*zone 4*/
							if(terrain[x-i][y-j][sol+1+hauteur]==0) terrain[x-i][y-j][sol+1+hauteur] = idTex;
						}
					}
				}
			}
		}
	}
	
	//Donne la coordonnée du sol en fonction de la position
	int Terrain::getSolCoordonnee(glm::vec3 position){
		glm::vec3 cubePosition = glm::floor(glm::abs(position));
		int X = cubePosition.x;
		int Z = cubePosition.z;
		int k = cubePosition.y+1;
		while ( terrain[X][Z][k] == 0 && k > 0){
			k--;
		}
		return k;
	}
	
	int Terrain::getNearestCollisionX(glm::vec3 position){
		//Hauteur du perso => +1
		int z = position.y + 1;
		int y = -position.z;
		int y1 = -position.z;
		
		if( (int)(-position.z + SPEED_DEPLACEMENT) != y ) y1 = y + 1;
		if( (int)(-position.z - SPEED_DEPLACEMENT) != y ) y1 = y - 1;

		int pos, neg;
		int i=glm::ceil(position.x);
		while(i<LONGUEUR_TERRRAIN && terrain[i][y][z] == 0 && terrain[i][y][z+1] == 0){
			i++;
		}
		pos=i;
		
		i=glm::floor(position.x);
		while(i>0 && terrain[i][y][z] == 0 && terrain[i][y][z+1] == 0){
			i--;
		}
		neg=i;
		
		if( y1 != y ){
			
			i=glm::ceil(position.x);
			while(y1<LONGUEUR_TERRRAIN && terrain[i][y1][z] == 0 && terrain[i][y1][z+1] == 0){
				i++;
			}
			if( i < pos ) pos = i;
			
			i=glm::floor(position.x);
			while(i>0 && terrain[i][y1][z] == 0 && terrain[i][y1][z+1] == 0){
				i--;
			}
			if( i > neg ) neg = i;
		}
		
		// On retourne pos ou neg en fonction de la direction vers laquelle la collision est la plus proche
		//Cas special bord map
		if( position.x<2 ){
			if(glm::abs(position.x-(float)pos) < glm::abs(position.x-(float)(neg))) return pos;
			else if( terrain[0][y][z] == 0 && terrain[0][y1][z] == 0 ) return neg;
			else return neg+1;
		}
		//Cas general
		else {
			if(glm::abs(position.x-(float)pos) < glm::abs(position.x-(float)(neg+1))) {std::cout<<"pos : "<<pos<<std::endl;return pos; }
			else {std::cout<<"neg : "<<neg+1<<std::endl;return neg + 1;}
		}

	}
			
	int Terrain::getNearestCollisionY(glm::vec3 position){
		//Hauteur du perso => +1
		int z = position.y + 1;
		int x = position.x ;
		int x1 = position.x;
		
		if( ((int)(position.x + SPEED_DEPLACEMENT)) != x ) x1 = x + 1;
		if( ((int)(position.x - SPEED_DEPLACEMENT)) != x ) x1 = x - 1;
		
		int pos, neg;
		int j=glm::ceil(-position.z);
		while(j<LARGEUR_TERRRAIN && terrain[x][j][z] == 0 && terrain[x][j][z+1] == 0){
			j++;
		}
		pos=j;
		j=glm::floor(-position.z);
		while(j>0 && terrain[x][j][z] == 0 && terrain[x][j][z+1] == 0){
			j--;
		}
		neg=j;
		
		if( x1 != x ){
			
			j=glm::ceil(-position.z);
			while(j<LONGUEUR_TERRRAIN && terrain[x1][j][z] == 0 && terrain[x1][j][z+1] == 0){
				j++;
			}
			if( j < pos ) pos = j;
			
			j=glm::floor(-position.z);
			while(j>0 && terrain[x1][j][z] == 0 && terrain[x1][j][z+1] == 0){
				j--;
			}
			if( j > neg ) neg = j;
		}
		
		// On retourne pos ou neg en fonction de la direction vers laquelle la collision est la plus proche
		//Cas special bord map
		if( -position.z<2 ){
			if(glm::abs((-position.z)-(float)pos) < glm::abs((-position.z)-(float)(neg))) return pos;
			else if( terrain[x][0][z] == 0 && terrain[x1][0][z] == 0 ) return neg;
			else return neg+1;
		}
		//Cas general
		else {
			if(glm::abs((-position.z)-(float)pos) < glm::abs((-position.z)-(float)(neg+1))) return pos;
			else return neg+1;
		}
		
	}
	
	bool Terrain::randomBool(int balance){
		if (rand()%100 < balance) return true;
		else return false;
	}
	
	int Terrain::randomPosition(char vecteur){
		if (vecteur == 'x') return rand()%LARGEUR_TERRRAIN;
		if (vecteur == 'y') return rand()%LONGUEUR_TERRRAIN;
		if (vecteur == 'z') return rand()%HAUTEUR_TERRRAIN;
		return 0;
	}
	
	int Terrain::randomBalance(int balance){
		if (balance < 0) return 0;
		return rand()%balance;
	}
	
	void Terrain::save(){
		ofstream fichier("save/test.txt", ios::out | ios::trunc);
		if(fichier)
		{
			int longueur = LONGUEUR_TERRRAIN;
			int largeur = LARGEUR_TERRRAIN;
			int hauteur = HAUTEUR_TERRRAIN;
			fichier << longueur << " " << largeur << " " << hauteur << endl;
			for(int i=0; i<LONGUEUR_TERRRAIN; ++i)
			{
				for(int j=0; j<LARGEUR_TERRRAIN; ++j)
				{
					for(int k=0; k<HAUTEUR_TERRRAIN; ++k)
					{
						fichier << terrain[i][j][k];
						if(k == HAUTEUR_TERRRAIN-1) fichier << std::endl;
					}
				}
			}
			fichier.close();
		}
		else cerr << "Impossible d'ouvrir le fichier !" << endl;
	}

}
