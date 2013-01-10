#include <iostream>
#include <cstdlib>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ctime>
#include "imac2gl3/settings.hpp"

#include "imac2gl3/shapes/Terrain.hpp"
#include "imac2gl3/shader_tools.hpp"
#include "imac2gl3/frameClocker.hpp"
#include "imac2gl3/shapes/GLShapeInstance.hpp"
#include "imac2gl3/shapes/MatrixStack.hpp"
#include "imac2gl3/cameras/FreeFlyCamera.hpp"

int main(int argc, char** argv) {
    /********************************************************************
     * INITIALISATION DU PROGRAMME
     ********************************************************************/
    
    std::string nom;
    
    // Init setup Audio
    Mix_OpenAudio(44100,AUDIO_S16SYS,2,10000);
    Mix_AllocateChannels(5);
    Mix_Volume(1,MIX_MAX_VOLUME/2);
    
    // Chargement sample
    Mix_Music *ambient;  // For Long noise music
    Mix_Chunk *crash, *add, *stepGrass, *stepGround, *stepWood, *pluck;  // For Sounds
    crash = Mix_LoadWAV("son/crash.wav");
    if(!crash) {
	std::cout<<"Impossible charger sample"<<std::endl;
    }
    add = Mix_LoadWAV("son/add.wav");
    if(!add) {
	std::cout<<"Impossible charger sample"<<std::endl;
    }
    stepGrass = Mix_LoadWAV("son/stepGrass.wav");
    if(!stepGrass) {
	std::cout<<"Impossible charger sample"<<std::endl;
    }
    stepGround = Mix_LoadWAV("son/stepGround.wav");
    if(!stepGround) {
	std::cout<<"Impossible charger sample"<<std::endl;
    }
    stepWood = Mix_LoadWAV("son/stepWood.wav");
    if(!stepWood) {
	std::cout<<"Impossible charger sample"<<std::endl;
    }
    pluck = Mix_LoadWAV("son/pluck.wav");
    if(!pluck) {
	std::cout<<"Impossible charger sample"<<std::endl;
    }
    ambient = Mix_LoadMUS("son/ambient.wav");
    if(!ambient) {
	std::cout<<"Impossible charger sample"<<std::endl;
    }
    Mix_PlayMusic(ambient, 1);
    
    // Propagation d'une graine pour le random
    srand(time(NULL)); // On prend le nombre de secondes ecoulees depuis le commencement
    
    // Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // Creation de la fenêtre et d'un contexte OpenGL
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BYTES_PER_PIXEL, SDL_OPENGL);

    // Initialisation de GLEW
    GLenum error;
    if(GLEW_OK != (error = glewInit())) {
        std::cerr << "Impossible d'initialiser GLEW: " << glewGetErrorString(error) << std::endl;
        return EXIT_FAILURE;
    }

    // Creation du Terrain
    imac2gl3::Terrain terrain;
	
    // Creation de la matrice de Perspective
    glm::mat4 P = glm::perspective(70.f, WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 1000.f);
    
    // Creation de la Camera
    glm::vec3 startPosition((LARGEUR_TERRRAIN)/2.1, HAUTEUR_TERRRAIN-2 , -(LONGUEUR_TERRRAIN)/2.1);
    imac2gl3::FreeFlyCamera Cam(startPosition, &terrain);

    glEnable(GL_DEPTH_TEST);

    
    // Boucle principale
    bool done = false;
    while(!done) {
		
		imac2gl3::FrameClocker frameClocker;
		
        // Nettoyage de la fenêtre
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// Creation de la matrice de Vue
		glm::mat4 V = Cam.getViewMatrix();

		MatrixStack mstack;
		mstack.mult(P);
		mstack.mult(V);

		//Dessin du terrain
		terrain.draw(mstack, Cam.getPosition(), 30);
        
        //Evenements souris
        SDL_Event e;
        int mouse_x, mouse_y, old_mouse_x, old_mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		Cam.rotateLeft( (old_mouse_x - mouse_x) * MOUSE_SENSITIVITY );
		Cam.rotateUp( (old_mouse_y - mouse_y) * MOUSE_SENSITIVITY );
		old_mouse_x = mouse_x;
		old_mouse_y = mouse_y;
			
        //Evenements claviers
        Uint8 *keystate = SDL_GetKeyState(NULL);
        
        if( keystate[SDLK_z] && !keystate[SDLK_q] && !keystate[SDLK_d] ) Cam.moveFront(SPEED_DEPLACEMENT, stepGrass, stepGround, stepWood);
        else if( keystate[SDLK_z] ) Cam.moveFront(SPEED_DEPLACEMENT/sqrt(2), stepGrass, stepGround, stepWood);
        
		if( keystate[SDLK_s] && !keystate[SDLK_q] && !keystate[SDLK_d] ) Cam.moveFront(-SPEED_DEPLACEMENT, stepGrass, stepGround, stepWood);
		else if( keystate[SDLK_s] ) Cam.moveFront(-SPEED_DEPLACEMENT/sqrt(2), stepGrass, stepGround, stepWood);
		
		if( keystate[SDLK_q] && !keystate[SDLK_z] && !keystate[SDLK_s] ) Cam.moveLeft(SPEED_DEPLACEMENT, stepGrass, stepGround, stepWood);
		else if( keystate[SDLK_q] ) Cam.moveLeft(SPEED_DEPLACEMENT/sqrt(2), stepGrass, stepGround, stepWood);
		
		if( keystate[SDLK_d] && !keystate[SDLK_z] && !keystate[SDLK_s] ) Cam.moveLeft(-SPEED_DEPLACEMENT, stepGrass, stepGround, stepWood);
		else if( keystate[SDLK_d] ) Cam.moveLeft(-SPEED_DEPLACEMENT/sqrt(2), stepGrass, stepGround, stepWood);
		
		if( keystate[SDLK_SPACE] ) Cam.jumpLaunch(0.4);
		
		// Break propagation

		//Pesanteur
		Cam.moveUp(-SPEED_DEPLACEMENT);
		
        // Traitement de l'évenement fermeture de fenêtre
        while(SDL_PollEvent(&e)) {
	    switch(e.type){
            case SDL_QUIT :
                done = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
				switch(e.button.button){
					case SDL_BUTTON_LEFT:
						Cam.breakBlock(crash);
						break;
					case SDL_BUTTON_RIGHT:
						Cam.createBlock(add);
						break;
					
					default: break;
				}
            
			case SDL_KEYDOWN :
				switch(e.key.keysym.sym)
				{
					case SDLK_a:
					Mix_PlayChannel(1,pluck,0);
					terrain.save(Cam.getPosition());
					std::cout<<"Terrain saved"<<std::endl;
    					break;
					case SDLK_l:
					Mix_PlayChannel(1,pluck,0);
					std::cout << "Nom du fichier a charger :" <<std::endl;
					std::cin >> nom;
					terrain.load(nom);
					
					std::cout<<"Terrain loaded"<<std::endl;
					Cam.setPositionY(terrain.loadPositionCam(nom, 'y')+2); //Hauteur (positive)
					Cam.setPositionX(terrain.loadPositionCam(nom, 'x'));
					Cam.setPositionZ(terrain.loadPositionCam(nom, 'z'));
					std::cout<<"Camera loaded"<<std::endl;
					
					break;
					default: break;
				}
			
	    }
        }
        
        // Mise à jour de l'affichage
        SDL_GL_SwapBuffers();
        
        //Cam.afficherCam();
        
    }
    
    // Destruction des ressources
    Mix_FreeChunk(crash);
    crash = NULL;
    Mix_CloseAudio();
    Mix_Quit();
   
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
