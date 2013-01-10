#include "imac2gl3/shapes/Terrain.hpp"

using namespace std;

namespace imac2gl3 {
	
	enum blocs{ vide=0, terre=1, herbe=2, eau=3, roche=4, neige=5, bois=9 };

	
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
		int hauteurMax = 5;
		// Construction du terrain entier, tout est rempli et par couche (texture cube)
		for(int i=0; i<LONGUEUR_TERRRAIN; ++i){
			for(int j=0; j<LARGEUR_TERRRAIN; ++j){
				for(int k=0; k<HAUTEUR_TERRRAIN; ++k){
					if(k<=sol)
					{
						terrain(i, j, k) = terre;
					}
					else
					{
						terrain(i, j, k) = vide;
					}
				}	
			}
		}
		
		/* relief */
		for(int i = 1; i<10000; ++i) make(randomBalance(hauteurMax), 8, randomPosition('x'), randomPosition('y'), sol, herbe); // montagne
		for(int i = 1; i<1000; ++i) blockRemove(5, 5, randomPosition('x'), randomPosition('y'), sol+4); // creux
		
		/* routine */
		for(int i=0; i<LONGUEUR_TERRRAIN; ++i){
			for(int j=0; j<LARGEUR_TERRRAIN; ++j){
				for(int k=0; k<HAUTEUR_TERRRAIN; ++k){
					if(terrain(i, j, k) == herbe && terrain(i, j, k+1) != vide)
					{
						terrain(i, j, k) = terre;
					}
					if(terrain(i, j, k) == terre && terrain(i, j, k+1) == vide)
					{
						terrain(i, j, k) = herbe;
					}
				}	
			}
		}
		
		for(int i = 1; i<2000; ++i) make(1, randomBalance(hauteurMax), randomPosition('x'), randomPosition('y'), sol+hauteurMax-1, roche);
		
		/* routine */
		for(int i=0; i<LONGUEUR_TERRRAIN; ++i){
			for(int j=0; j<LARGEUR_TERRRAIN; ++j){
				for(int k=0; k<HAUTEUR_TERRRAIN; ++k){
					if(terrain(i, j, k) == roche && terrain(i, j, k-1) == vide)
					{
						terrain(i, j, k) = vide;
					}
				}	
			}
		}

		
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
		
		GLShapeInstance* cube = new GLShapeInstance(myCubeTerre);
		int lastCubeDrawn = 0;	
		for(int i=imin; i<=imax; ++i) 
			for(int j=jmin; j<=jmax; ++j)
				for(int k=kmin; k<=kmax; ++k)
				{
					if (hasFreeSurface(i, j, k)){
						
						if(terrain(i, j, k) == terre){
							
							if( lastCubeDrawn != terre){
								delete cube;
								cube = new GLShapeInstance(myCubeTerre);
								glActiveTexture(GL_TEXTURE0);
								glBindTexture(GL_TEXTURE_2D, cube->getTexture());
								lastCubeDrawn = terre;
							}
							
							mstack.push();
							mstack.translate(glm::vec3(i, k, -j));
							
							//Transmission de la matrice MVP au vertex shader
							glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mstack.top()));
							
							cube->draw();
							
							mstack.pop();
							
						}
							
						if(terrain(i, j, k) == herbe){
							
							
							if( lastCubeDrawn != herbe){
								delete cube;
								cube = new GLShapeInstance(myCubeHerbe);
								glActiveTexture(GL_TEXTURE0);
								glBindTexture(GL_TEXTURE_2D, cube->getTexture());
								lastCubeDrawn = herbe;
							}
							
							mstack.push();
							mstack.translate(glm::vec3(i, k, -j));
							
							//Transmission de la matrice MVP au vertex shader
							glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mstack.top()));
							
							cube->draw();
							
							mstack.pop();
						}
						
						if(terrain(i, j, k) == eau){
							
							if( lastCubeDrawn != eau){
								delete cube;
								cube = new GLShapeInstance(myCubeEau);
								glActiveTexture(GL_TEXTURE0);
								glBindTexture(GL_TEXTURE_2D, cube->getTexture());
								lastCubeDrawn = eau;
							}
							
							mstack.push();
							mstack.translate(glm::vec3(i, k, -j));
							
							//Transmission de la matrice MVP au vertex shader
							glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mstack.top()));
							
							cube->draw();
							
							mstack.pop();
						}
						
						if(terrain(i, j, k) == roche){
							
							if( lastCubeDrawn != roche){
								delete cube;
								cube = new GLShapeInstance(myCubeRoche);
								glActiveTexture(GL_TEXTURE0);
								glBindTexture(GL_TEXTURE_2D, cube->getTexture());
								lastCubeDrawn = roche;
							}
							
							mstack.push();
							mstack.translate(glm::vec3(i, k, -j));
							
							//Transmission de la matrice MVP au vertex shader
							glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mstack.top()));
							
							cube->draw();
							
							mstack.pop();
						}
						
						if(terrain(i, j, k) == bois){
							
							
							if( lastCubeDrawn != bois){
								delete cube;
								cube = new GLShapeInstance(myCubeBois);
								glActiveTexture(GL_TEXTURE0);
								glBindTexture(GL_TEXTURE_2D, cube->getTexture());
								lastCubeDrawn = bois;
							}
							
							mstack.push();
							mstack.translate(glm::vec3(i, k, -j));
							
							//Transmission de la matrice MVP au vertex shader
							glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mstack.top()));
							
							cube->draw();
							
							mstack.pop();
						}
					}
				}
		
		//Skybox
		delete cube;
		cube = new GLShapeInstance(mySkybox);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cube->getTexture());
		
		mstack.push();
		mstack.translate(position);
		
		//Transmission de la matrice MVP au vertex shader
		glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mstack.top()));
		
		cube->draw();
		
		mstack.pop();
		
		delete cube;
	}
	
	void Terrain::make(int height, int width, int x, int y, int sol, int id_Tex){
		int idTex = id_Tex;
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
	
	void Terrain::blockRemove(int height, int width, int x, int y, int sol){
		int idTex = vide;
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
	
	bool Terrain::addBlock(int x, int y, int z, Mix_Chunk *son){
		int sol = getSolCoordonnee(glm::vec3(x,y,z));
		if(terrain(x, -z, y) == 0 && hasFreeSurface(x, -z, y) && y >= sol+1){
			terrain(x, -z, sol+1) = bois;
			Mix_PlayChannel(1,son,0);
			return true;
		}
		else return false;
	}
	
	bool Terrain::deleteBlock(int x, int y, int z, Mix_Chunk *son){
		if(blocDestructable(x, -z, y) && hasFreeSurface(x, -z, y)){
			terrain(x, -z, y) = vide;
			Mix_PlayChannel(1,son,0); 
			return true;
		}
		else return false;
	}
	
	int Terrain::getId(int x, int y, int z){
		return terrain(x, y, z);
	}
	
	bool Terrain:: blocDestructable(int i, int j, int k) const {
		int bloc = terrain(i, j, k);
		if( bloc == terre ) return myCubeTerre.getDestructable();
		if( bloc == herbe ) return myCubeHerbe.getDestructable();
		if( bloc == eau ) return myCubeEau.getDestructable();
		if( bloc == roche ) return myCubeRoche.getDestructable();
		//if( bloc == neige ) return myCubeNeige.getDestructable();
		if( bloc == bois ) return myCubeBois.getDestructable();
	}
	
	bool Terrain::hasFreeSurface(int i, int j, int k) const {
		int imax = std::min(i+1, LONGUEUR_TERRRAIN-1);
		int imin = std::max(i-1, 0);
		int jmax = std::min(j+1, LARGEUR_TERRRAIN-1);
		int jmin = std::max(j-1, 0);
		int kmax = std::min(k+1, HAUTEUR_TERRRAIN-1);
		int kmin = std::max(k-1, 0);
		
			if(
				terrain(imax, j, k) == vide || 
				terrain(imin, j, k) == vide ||
				terrain(i, jmax, k) == vide ||
				terrain(i, jmin, k) == vide ||
				terrain(i, j, kmax) == vide ||
				terrain(i, j, kmin) == vide ) return true;
			else return false;
	}
	
	//Donne la coordonnée du sol en fonction de la position
	int Terrain::getSolCoordonnee(glm::vec3 position) const{
		glm::vec3 cubePosition = glm::floor(glm::abs(position));
		int X = cubePosition.x;
		int Z = cubePosition.z;
		int k = cubePosition.y+1;
		while ( terrain(X, Z, k) == vide && k > 0){
			k--;
		}
		return k;
	}
	
	int Terrain::getNearestCollisionX(glm::vec3 position) const{
		//Hauteur du perso => +1
		int z = position.y + 1;
		int y = -position.z;
		int y1 = -position.z;
		
		if( (int)(-position.z + SPEED_DEPLACEMENT) != y ) y1 = y + 1;
		if( (int)(-position.z - SPEED_DEPLACEMENT) != y ) y1 = y - 1;

		int pos, neg;
		int i=glm::ceil(position.x);
		while(i<position.x+2 && i<LONGUEUR_TERRRAIN && terrain(i, y, z) == vide && terrain(i, y, z+1) == vide){
			i++;
		}
		pos=i;
		
		i=glm::floor(position.x);
		while(i>position.x-2 && i>0 && terrain(i, y, z) == vide && terrain(i, y, z+1) == vide){
			i--;
		}
		neg=i;
		
		if( y1 != y ){
			
			i=glm::ceil(position.x);
			while(i<position.x+2 && i<LONGUEUR_TERRRAIN && terrain(i, y1, z) == vide && terrain(i, y1, z+1) == vide){
				i++;
			}
			if( i < pos ) pos = i;
			
			i=glm::floor(position.x);
			while(i>position.x-2 && i>0 && terrain(i, y1, z) == vide && terrain(i, y1, z+1) == vide){
				i--;
			}
			if( i > neg ) neg = i;
		}
		
		// On retourne pos ou neg en fonction de la direction vers laquelle la collision est la plus proche
		//Cas special bord map
		if( position.x<2 ){
			if(glm::abs(position.x-(float)pos) < glm::abs(position.x-(float)(neg))) return pos;
			else if( terrain(0, y, z) == vide && terrain(0, y1, z) == vide ) return neg;
			else return neg+1;
		}
		//Cas general
		else {
			if(glm::abs(position.x-(float)pos) < glm::abs(position.x-(float)(neg+1))) return pos;
			else return neg + 1;
		}

	}
			
	int Terrain::getNearestCollisionY(glm::vec3 position) const{
		//Hauteur du perso => +1
		int z = position.y + 1;
		int x = position.x ;
		int x1 = position.x;
		
		if( ((int)(position.x + SPEED_DEPLACEMENT)) != x ) x1 = x + 1;
		if( ((int)(position.x - SPEED_DEPLACEMENT)) != x ) x1 = x - 1;
		
		int pos, neg;
		int j=glm::ceil(-position.z);
		while(j<(-position.z)+2 && j<LARGEUR_TERRRAIN && terrain(x, j, z) == vide && terrain(x, j, z+1) == vide){
			j++;
		}
		pos=j;
		j=glm::floor(-position.z);
		while(j>(-position.z)-2 && j>0 && terrain(x, j, z) == vide && terrain(x, j, z+1) == vide){
			j--;
		}
		neg=j;
		
		if( x1 != x ){
			
			j=glm::ceil(-position.z);
			while(j<(-position.z)+2 && j<LARGEUR_TERRRAIN && terrain(x1, j, z) == vide && terrain(x1, j, z+1) == vide){
				j++;
			}
			if( j < pos ) pos = j;
			
			j=glm::floor(-position.z);
			while(j>(-position.z)-2 && j>0 && terrain(x1, j, z) == vide && terrain(x1, j, z+1) == vide){
				j--;
			}
			if( j > neg ) neg = j;
		}
		
		// On retourne pos ou neg en fonction de la direction vers laquelle la collision est la plus proche
		//Cas special bord map
		if( -position.z<2 ){
			if(glm::abs((-position.z)-(float)pos) < glm::abs((-position.z)-(float)(neg))) return pos;
			else if( terrain(x, 0, z) == vide && terrain(x1, 0, z) == vide ) return neg;
			else return neg+1;
		}
		//Cas general
		else {
			if(glm::abs((-position.z)-(float)pos) < glm::abs((-position.z)-(float)(neg+1))) return pos;
			else return neg+1;
		}
		
		
	}
		
	void Terrain::save(glm::vec3 vecPos) const{
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
			fichier << "\t<z>" << endl << "\t\t" << vecPos.z  << endl << "\t</z>" << endl;
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
	
	float Terrain::loadPositionCam(string nom, char position3D){
		vector<string> list;
		int debut=0, fin=0;
		list.clear();
		string word;
		float position = -1;
		string racine = "save/";
		string ext = ".xml";
		string repertoire = racine + nom + ext;
		
		ifstream fichier;
		FileOpener opener(fichier, repertoire.c_str());
		
		if(fichier)
		{
			while (fichier >> word) {
			    list.push_back(word);
			}	   
			fichier.close();
			
			if(position3D=='y')
			{
				for(int i = 0; i<list.size(); i++){
					if(list.at(i) == "<y>") debut = i+1;
					if(list.at(i) == "</y>") fin = i;
				}
				position = atof(list.at(debut).c_str());
			}
			if(position3D=='x')
			{
				for(int i = 0; i<list.size(); i++){
					if(list.at(i) == "<x>") debut = i+1;
					if(list.at(i) == "</x>") fin = i;
				}
				position = atof(list.at(debut).c_str());
			}
			if(position3D=='z')
			{
				for(int i = 0; i<list.size(); i++){
					if(list.at(i) == "<z>") debut = i+1;
					if(list.at(i) == "</z>") fin = i;
				}
				position = atof(list.at(debut).c_str());
			}
			return position;
		}else cerr << "ERREUR OUVERTURE FICHIER" << endl;
		
	}
	
	void Terrain::load(string nom){
		vector<string> list;
		vector<char> listChar;
		vector<int> positionCube;
		int debut=0, fin=0;
		list.clear();
		string word;
		
		string racine = "save/";
		string ext = ".xml";
		string repertoire = racine + nom + ext;
		
		ifstream fichier;
		FileOpener opener(fichier, repertoire.c_str());
		
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
