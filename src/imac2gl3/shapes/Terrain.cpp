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
		int sol = 10;
		
		// Construction du terrain entier, tout est rempli et par couche (texture cube)
		for(int i=0; i<LONGUEUR_TERRRAIN; ++i){
			for(int j=0; j<LARGEUR_TERRRAIN; ++j){
				for(int k=0; k<HAUTEUR_TERRRAIN; ++k){
					if(k<=sol)
					{
						terrain(i, j, k) = 2;
					}
					else
					{
						terrain(i, j, k) = 0;
					}
				}	
			}
		}
		

		/* Chaine de montagnes */
		for(int i = 1; i<1000; ++i) relief(randomBalance(6), 15, randomPosition('x'), randomPosition('y'), sol);		
		//for(int j = 1; j<500; ++j) pyramid(15, randomBalance(8), randomPosition('x'), randomPosition('y'), sol);
		//for(int j = 1; j<20; ++j) pyramid(9, 9, randomPosition('x'), randomPosition('y'), sol);
		
		/* Check Cubes */
		for(int i=0; i<LONGUEUR_TERRRAIN; ++i){
			for(int j=0; j<LARGEUR_TERRRAIN; ++j){
				for(int k=0; k<HAUTEUR_TERRRAIN; ++k){
					if(k==0) terrain(i, j, k) = 2;
				}	
			}
		}
		
		/* Texturing */
		
	}
	
	void Terrain::afficherTerrain(){
		for(int i=0; i<LONGUEUR_TERRRAIN; ++i) 
		for(int j=0; j<LARGEUR_TERRRAIN; ++j)
			for(int k=0; k<HAUTEUR_TERRRAIN; ++k)
			{
				std::cout<<terrain(i, j, k);
				if(k == 9) std::cout<<std::endl;
			}
	}
	
	void Terrain::draw(MatrixStack &mstack, glm::vec3 position, int profondeur){
		
		//Compensation taille du cube
		mstack.translate(glm::vec3(0.5, -0.5, -0.5));
		
		//Compensation taille du personnage
		mstack.translate(glm::vec3(0, -1.5, 0));
		
		GLint uMVPMatrix = glGetUniformLocation(program, "uMVPMatrix");
		
		//Definition des bornes du dessin
		int imax = std::min( (int)position.x + profondeur, LONGUEUR_TERRRAIN-1 );
		int imin = std::max( (int)position.x - profondeur, 0 );
		int jmax = std::min( (int)(-position.z) + profondeur, LARGEUR_TERRRAIN-1 );
		int jmin = std::max( (int)(-position.z) - profondeur, 0 );
		int kmax = std::min( (int)position.y + profondeur, HAUTEUR_TERRRAIN-1 );
		int kmin = std::max( (int)position.y - profondeur, 0 );
		
		{
			//Boucle concernant le cube1
			//Bind de la Texture
			GLShapeInstance cube(myCube1);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cube.getTexture());
			
				for(int i=imin; i<imax; ++i) 
					for(int j=jmin; j<jmax; ++j)
						for(int k=kmin; k<kmax; ++k)
						{
							if(terrain(i, j, k) == 1 && hasFreeSurface(i, j, k)){
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
		
				for(int i=imin; i<imax; ++i) 
					for(int j=jmin; j<jmax; ++j)
						for(int k=kmin; k<kmax; ++k)
						{
							if(terrain(i, j, k) == 2 && hasFreeSurface(i, j, k)){
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
	
	void Terrain::relief(int height, int width, int x, int y, int sol){
		int idTex = 2;
		int aleaX, aleaY;
		for(int hauteur = 0; hauteur < height; ++hauteur)
		{
			if (hauteur == sol)
			{
				aleaX = 0;
				aleaY = 0;
			}
			else
			{
				aleaX = randomBalance(2);
				aleaY = randomBalance(2);
			}
			
			for(int i = 1; i<width-hauteur; ++i)
			{
				if
				(
					x+i+aleaX < LONGUEUR_TERRRAIN &&
					x-i+aleaX > 0 &&
					y+i+aleaY < LARGEUR_TERRRAIN &&
					y-i+aleaY > 0
				)
				{
					/* pivot montagne */
					if(terrain(x+aleaX, y+aleaY, sol+1+hauteur)==0) terrain(x+aleaX, y+aleaY, sol+1+hauteur) = idTex;
					/* etoile */
					if(terrain(x+i+aleaX, y+aleaY, sol+1+hauteur)==0) terrain(x+i+aleaX, y+aleaY, sol+1+hauteur) = idTex;
					if(terrain(x+aleaX, y+i+aleaY, sol+1+hauteur)==0) terrain(x+aleaX, y+i+aleaY, sol+1+hauteur) = idTex;
					if(terrain(x+aleaX, y-i+aleaY, sol+1+hauteur)==0) terrain(x+aleaX, y-i+aleaY, sol+1+hauteur) = idTex;
					if(terrain(x-i+aleaX, y+aleaY, sol+1+hauteur)==0) terrain(x-i+aleaX, y+aleaY, sol+1+hauteur) = idTex;
					for(int j = 1; j<width-hauteur; j++)
					{
						if
						(
							x+i+aleaX < LONGUEUR_TERRRAIN &&
							x-i+aleaX > 0 &&
							y+i+aleaY < LARGEUR_TERRRAIN &&
							y-i+aleaY > 0
						)
						{
							/*zone 1*/
							if(terrain(x+i+aleaX, y+j+aleaY, sol+1+hauteur)==0) terrain(x+i+aleaX, y+j+aleaY, sol+1+hauteur) = idTex;
							/*zone 2*/
							if(terrain(x+i+aleaX, y-j+aleaY, sol+1+hauteur)==0) terrain(x+i+aleaX, y-j+aleaY, sol+1+hauteur) = idTex;
							/*zone 3*/
							if(terrain(x-i+aleaX, y+j+aleaY, sol+1+hauteur)==0) terrain(x-i+aleaX, y+j+aleaY, sol+1+hauteur) = idTex;
							/*zone 4*/
							if(terrain(x-i+aleaX, y-j+aleaY, sol+1+hauteur)==0) terrain(x-i+aleaX, y-j+aleaY, sol+1+hauteur) = idTex;
						}
					}
				}
			}
		}
	}
	
	void Terrain::water(int length, int width, int x, int y, int sol){
		int idTex = 1;
		for(int hauteur = 0; hauteur < length; ++hauteur)
		{
			for(int i = 1; i<width-length; ++i)
			{
				if
				(
					x+i < LONGUEUR_TERRRAIN &&
					x-i > 0 &&
					y+i < LARGEUR_TERRRAIN &&
					y-i > 0
				)
				{
					/* pivot */
					if(terrain(x, y, sol+1+hauteur)==0) terrain(x, y, sol+1+hauteur) = idTex;
					/* etoile */
					if(terrain(x+i, y, sol+1+hauteur)==0) terrain(x+i, y, sol+1+hauteur) = idTex;
					if(terrain(x, y+i, sol+1+hauteur)==0) terrain(x, y+i, sol+1+hauteur) = idTex;
					if(terrain(x, y-i, sol+1+hauteur)==0) terrain(x, y-i, sol+1+hauteur) = idTex;
					if(terrain(x-i, y, sol+1+hauteur)==0) terrain(x-i, y, sol+1+hauteur) = idTex;
					for(int j = 1; j<width-hauteur; j++)
					{
						if
						(
							x+i < LONGUEUR_TERRRAIN &&
							x-i > 0 &&
							y+i < LARGEUR_TERRRAIN &&
							y-i > 0
						)
						{
							/*zone 1*/
							if(terrain(x+i, y+j, sol+1+hauteur)==0) terrain(x+i, y+j, sol+1+hauteur) = idTex;
							/*zone 2*/
							if(terrain(x+i, y-j, sol+1+hauteur)==0) terrain(x+i, y-j, sol+1+hauteur) = idTex;
							/*zone 3*/
							if(terrain(x-i, y+j, sol+1+hauteur)==0) terrain(x-i, y+j, sol+1+hauteur) = idTex;
							/*zone 4*/
							if(terrain(x-i, y-j, sol+1+hauteur)==0) terrain(x-i, y-j, sol+1+hauteur) = idTex;
						}
					}
				}
			}
		}
	}
	
	void Terrain::pyramid(int height, int width, int x, int y, int sol){
		blockRemove(10, width+1, x, y, sol);
		int idTex = 1;
		for(int hauteur = 0; hauteur < height; ++hauteur)
		{
			for(int i = 1; i<width-hauteur; ++i)
			{
				if
				(
					x+i < LONGUEUR_TERRRAIN &&
					x-i > 0 &&
					y+i < LARGEUR_TERRRAIN &&
					y-i > 0
				)
				{
					/* pivot */
					terrain(x, y, sol+1+hauteur) = idTex;
					/* etoile */
					terrain(x+i, y, sol+1+hauteur) = idTex;
					terrain(x, y+i, sol+1+hauteur) = idTex;
					terrain(x, y-i, sol+1+hauteur) = idTex;
					terrain(x-i, y, sol+1+hauteur) = idTex;
					for(int j = 1; j<width-hauteur; j++)
					{
						if
						(
							x+i < LONGUEUR_TERRRAIN &&
							x-i > 0 &&
							y+i < LARGEUR_TERRRAIN &&
							y-i > 0
						)
						{
							/*zone 1*/
							terrain(x+i, y+j, sol+1+hauteur) = idTex;
							/*zone 2*/
							terrain(x+i, y-j, sol+1+hauteur) = idTex;
							/*zone 3*/
							terrain(x-i, y+j, sol+1+hauteur) = idTex;
							/*zone 4*/
							terrain(x-i, y-j, sol+1+hauteur) = idTex;
						}
					}
				}
			}
			
		}
	}
	
	void Terrain::blockRemove(int height, int width, int x, int y, int sol){
		int idTex = 0;
		for(int hauteur = 0; hauteur < height; ++hauteur)
		{
			for(int i = 1; i<width; ++i)
			{
				if
				(
					x+i < LONGUEUR_TERRRAIN &&
					x-i > 0 &&
					y+i < LARGEUR_TERRRAIN &&
					y-i > 0
				)
				{
					/* pivot */
					terrain(x, y, sol+1+hauteur) = idTex;
					/* etoile */
					terrain(x+i, y, sol+1+hauteur) = idTex;
					terrain(x, y+i, sol+1+hauteur) = idTex;
					terrain(x, y-i, sol+1+hauteur) = idTex;
					terrain(x-i, y, sol+1+hauteur) = idTex;
					for(int j = 1; j<width; j++)
					{
						if
						(
							x+i < LONGUEUR_TERRRAIN &&
							x-i > 0 &&
							y+i < LARGEUR_TERRRAIN &&
							y-i > 0
						)
						{
							/*zone 1*/
							terrain(x+i, y+j, sol+1+hauteur) = idTex;
							/*zone 2*/
							terrain(x+i, y-j, sol+1+hauteur) = idTex;
							/*zone 3*/
							terrain(x-i, y+j, sol+1+hauteur) = idTex;
							/*zone 4*/
							terrain(x-i, y-j, sol+1+hauteur) = idTex;
						}
					}
				}
			}
			
		}
	}
	
	void Terrain::cavity(int height, int width, int x, int y, int sol){
		int idTex = 0;
		int aleaX, aleaY;
		for(int hauteur = 0; hauteur < height; ++hauteur)
		{
			if (hauteur == sol)
			{
				aleaX = 0;
				aleaY = 0;
			}
			else
			{
				aleaX = randomBalance(2);
				aleaY = randomBalance(2);
			}
			
			for(int i = 1; i<width-hauteur; ++i)
			{
				if
				(
					x+i+aleaX < LONGUEUR_TERRRAIN &&
					x-i+aleaX  > 0 &&
					y+i+aleaY < LARGEUR_TERRRAIN &&
					y-i+aleaY > 0
				)
				{
					/* pivot cavite */
					if(terrain(x+aleaX, y+aleaY, sol-hauteur)!=0) terrain(x+aleaX ,y+aleaY , sol-hauteur) = idTex;
					/* etoile */
					if(terrain(x+i+aleaX, y+aleaY, sol-hauteur)!=0) terrain(x+i+aleaX, y+aleaY, sol-hauteur) = idTex;
					if(terrain(x+aleaX, y+i+aleaY, sol-hauteur)!=0) terrain(x+aleaX, y+i+aleaY, sol-hauteur) = idTex;
					if(terrain(x+aleaX, y-i+aleaY, sol-hauteur)!=0) terrain(x+aleaX, y-i+aleaY, sol-hauteur) = idTex;
					if(terrain(x-i+aleaX, y+aleaY, sol-hauteur)!=0) terrain(x-i+aleaX, y+aleaY, sol-hauteur) = idTex;
					for(int j = 1; j<width-hauteur; j++)
					{
						if
						(
							x+i+aleaX < LONGUEUR_TERRRAIN &&
							x-i+aleaX > 0 &&
							y+i+aleaY < LARGEUR_TERRRAIN &&
							y-i+aleaY > 0
						)
						{
							/*zone 1*/
							if(terrain(x+i+aleaX, y+j+aleaY, sol-hauteur)!=0) terrain(x+i+aleaX, y+j+aleaY, sol-hauteur) = idTex;
							/*zone 2*/
							if(terrain(x+i+aleaX, y-j+aleaY, sol-hauteur)!=0) terrain(x+i+aleaX, y-j+aleaY, sol-hauteur) = idTex;
							/*zone 3*/
							if(terrain(x-i+aleaX, y+j+aleaY, sol-hauteur)!=0) terrain(x-i+aleaX, y+j+aleaY, sol-hauteur) = idTex;
							/*zone 4*/
							if(terrain(x-i+aleaX, y-j+aleaY, sol-hauteur)!=0) terrain(x-i+aleaX, y-j+aleaY, sol-hauteur) = idTex;
						}
					}
				}
			}
		}
	}
	
	void Terrain::addBlock(int x, int y, int z){
		
	}
	void Terrain::deleteBlock(int x, int y, int z){
		
	}
	
	bool Terrain::hasFreeSurface(int i, int j, int k){
		int imax = std::min(i+1, LONGUEUR_TERRRAIN-1);
		int imin = std::max(i-1, 0);
		int jmax = std::min(j+1, LARGEUR_TERRRAIN-1);
		int jmin = std::max(j-1, 0);
		int kmax = std::min(k+1, HAUTEUR_TERRRAIN-1);
		int kmin = std::max(k-1, 0);
		
			if(
				terrain(imax, j, k) == 0 || 
				terrain(imin, j, k) == 0 ||
				terrain(i, jmax, k) == 0 ||
				terrain(i, jmin, k) == 0 ||
				terrain(i, j, kmax) == 0 ||
				terrain(i, j, kmin) == 0 ) return true;
			else return false;
	}
	
	//Donne la coordonnée du sol en fonction de la position
	int Terrain::getSolCoordonnee(glm::vec3 position){
		glm::vec3 cubePosition = glm::floor(glm::abs(position));
		int X = cubePosition.x;
		int Z = cubePosition.z;
		int k = cubePosition.y+1;
		while ( terrain(X, Z, k) == 0 && k > 0){
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
		while(i<LONGUEUR_TERRRAIN && terrain(i, y, z) == 0 && terrain(i, y, z+1) == 0){
			i++;
		}
		pos=i;
		
		i=glm::floor(position.x);
		while(i>0 && terrain(i, y, z) == 0 && terrain(i, y, z+1) == 0){
			i--;
		}
		neg=i;
		
		if( y1 != y ){
			
			i=glm::ceil(position.x);
			while(i<LONGUEUR_TERRRAIN && terrain(i, y1, z) == 0 && terrain(i, y1, z+1) == 0){
				i++;
			}
			if( i < pos ) pos = i;
			
			i=glm::floor(position.x);
			while(i>0 && terrain(i, y1, z) == 0 && terrain(i, y1, z+1) == 0){
				i--;
			}
			if( i > neg ) neg = i;
		}
		
		// On retourne pos ou neg en fonction de la direction vers laquelle la collision est la plus proche
		//Cas special bord map
		if( position.x<2 ){
			if(glm::abs(position.x-(float)pos) < glm::abs(position.x-(float)(neg))) return pos;
			else if( terrain(0, y, z) == 0 && terrain(0, y1, z) == 0 ) return neg;
			else return neg+1;
		}
		//Cas general
		else {
			if(glm::abs(position.x-(float)pos) < glm::abs(position.x-(float)(neg+1))) return pos;
			else return neg + 1;
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
		while(j<LARGEUR_TERRRAIN && terrain(x, j, z) == 0 && terrain(x, j, z+1) == 0){
			j++;
		}
		pos=j;
		j=glm::floor(-position.z);
		while(j>0 && terrain(x, j, z) == 0 && terrain(x, j, z+1) == 0){
			j--;
		}
		neg=j;
		
		if( x1 != x ){
			
			j=glm::ceil(-position.z);
			while(j<LONGUEUR_TERRRAIN && terrain(x1, j, z) == 0 && terrain(x1, j, z+1) == 0){
				j++;
			}
			if( j < pos ) pos = j;
			
			j=glm::floor(-position.z);
			while(j>0 && terrain(x1, j, z) == 0 && terrain(x1, j, z+1) == 0){
				j--;
			}
			if( j > neg ) neg = j;
		}
		
		// On retourne pos ou neg en fonction de la direction vers laquelle la collision est la plus proche
		//Cas special bord map
		if( -position.z<2 ){
			if(glm::abs((-position.z)-(float)pos) < glm::abs((-position.z)-(float)(neg))) return pos;
			else if( terrain(x, 0, z) == 0 && terrain(x1, 0, z) == 0 ) return neg;
			else return neg+1;
		}
		//Cas general
		else {
			if(glm::abs((-position.z)-(float)pos) < glm::abs((-position.z)-(float)(neg+1))) return pos;
			else return neg+1;
		}
		
	}
		
	void Terrain::save(glm::vec3 vecPos){
		string nom;
		cout << "Nom du fichier a enregistrer :" <<endl;
		cin >> nom;
		string racine = "save/";
		string ext = ".xml";
		string repertoire = racine + nom + ext;
		cout<<repertoire<<endl;
		ofstream fichier(repertoire.c_str(), ios::out | ios::trunc);
		if(fichier)
		{
			int longueur = LONGUEUR_TERRRAIN;
			int largeur = LARGEUR_TERRRAIN;
			int hauteur = HAUTEUR_TERRRAIN;
			fichier << "<nomJeu>" << endl << "\t" << "Minecraft IMAC" << endl << "</nomJeu>" << endl;
			fichier << "<nomFichier>" << endl << "\t" << nom << endl << "</nomFichier>" << endl;
			fichier << "<proprieteTerrain>" << endl;
			fichier << "\t<longueur>" << endl << "\t\t" << longueur << endl << "\t</longueur>" << endl;
			fichier << "\t<largeur>" << endl << "\t\t" << largeur << endl << "\t</largeur>" << endl;
			fichier << "\t<hauteur>" << endl << "\t\t" << hauteur << endl << "\t</hauteur>" << endl;
			fichier << "</proprieteTerrain>" << endl;
			fichier << "<positionPersonnage>" << endl;
			fichier << "\t<x>" << endl << "\t\t" << vecPos.x << endl << "\t</x>" << endl;
			fichier << "\t<y>" << endl << "\t\t" << vecPos.y << endl << "\t</y>" << endl;
			fichier << "\t<z>" << endl << "\t\t" << vecPos.z << endl << "\t</z>" << endl;
			fichier << "</positionPersonnage>" << endl;
			fichier << "<positionCube>" << endl;
			for(int i=0; i<LONGUEUR_TERRRAIN; ++i)
			{
				for(int j=0; j<LARGEUR_TERRRAIN; ++j)
				{
					for(int k=0; k<HAUTEUR_TERRRAIN; ++k)
					{
						fichier << terrain(i, j, k);
						if(k==HAUTEUR_TERRRAIN-1) fichier << endl;
					}
				}
			}
			fichier << "</positionCube>";
			fichier.close();
		}
		else cerr << "ERREUR ECRITURE" << endl;
	}
	
	void Terrain::load(){
		string nom;
		cout << "Nom du fichier a charger :" <<endl;
		cin >> nom;
		
		vector<string> list;
		vector<char> listChar;
		vector<int> positionCube;
		int debut=0, debutPerso=0, fin=0, finPerso=0;
		list.clear();
		string word;
		
		string racine = "save/";
		string ext = ".xml";
		string repertoire = racine + nom + ext;
		ifstream fichier(repertoire.c_str());
		
		if(fichier)
		{			
			while (fichier >> word) {
			    list.push_back(word);
			}
				   
			fichier.close();
			
			// Calcul du debut et fin des positions des cubes
			for(int i = 0; i<list.size(); i++){
				if(list.at(i) == "<positionCube>") debut = i+1;
				if(list.at(i) == "</positionCube>") fin = i;
				
				if(list.at(i) == "<positionPersonnage>") debutPerso = i+1;
				if(list.at(i) == "</positionPersonnage>") finPerso = i;
			}

			// Converti listes de string en liste de char
			for(int j = debut; j<fin; ++j)
			{
				const char *c = list.at(j).c_str();
				for(int k=0; k<HAUTEUR_TERRRAIN; ++k)
				{
					listChar.push_back(c[k]);
				}
			}
						
			// Converti char en int
			for(int j = 0; j<listChar.size(); ++j)
			{
				positionCube.push_back(static_cast<int>(listChar.at(j))-48);
			}
			
			// Mise a jour terrain
			for(int i=0; i<LONGUEUR_TERRRAIN; ++i)
			{
				for(int j=0; j<LARGEUR_TERRRAIN; ++j)
				{
					for(int k=0; k<HAUTEUR_TERRRAIN; ++k)
					{
						terrain(i, j, k) = positionCube[(i*( LARGEUR_TERRRAIN * HAUTEUR_TERRRAIN ) + j*HAUTEUR_TERRRAIN + k)];
					}
				}
			}
			
		}else cerr << "ERREUR OUVERTURE FICHIER" << endl;		
	}
}
