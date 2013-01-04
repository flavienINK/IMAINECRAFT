#ifndef _IMAC2GL3_CUBEHERBE_HPP_
#define _IMAC2GL3_CUBEHERBE_HPP_

#include <GL/glew.h>
#include <vector>

#include "common.hpp"
#include "imac2gl3/shapes/Cube.hpp"

namespace imac2gl3 {


class CubeHerbe: public Cube {
	
	private:
		GLuint texture;
		
	public:
		
		CubeHerbe(){
			SDL_Surface* tex2 = IMG_Load("img/herbe.png");
			
			glGenTextures(1, &texture);
		
			glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex2->w, tex2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex2->pixels);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			
			SDL_FreeSurface(tex2);
		};
		
		GLuint getTexture() const {
			return texture;
		};
};

}

#endif
