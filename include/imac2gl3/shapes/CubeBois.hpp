#ifndef _IMAC2GL3_CUBEBOIS_HPP_
#define _IMAC2GL3_CUBEBOIS_HPP_

#include <GL/glew.h>
#include <vector>

#include "common.hpp"
#include "imac2gl3/shapes/Cube.hpp"

namespace imac2gl3 {


class CubeBois: public Cube {
	
	private:
		GLuint texture;
		static const bool destructable = true;
		
	public:
		
		CubeBois(){
			SDL_Surface* tex1 = IMG_Load("img/bois.png");
		
			glGenTextures(1, &texture);
			
			glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex1->w, tex1->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex1->pixels);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			
			SDL_FreeSurface(tex1);
		};
		
		GLuint getTexture() const {
			return texture;
		};
		
		bool getDestructable() const {
			return destructable;
		};
};

}

#endif
