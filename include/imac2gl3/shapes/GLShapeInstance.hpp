#ifndef GLSHAPEINSTANCE_H
#define GLSHAPEINSTANCE_H

#include <cstddef>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imac2gl3/shader_tools.hpp"



namespace imac2gl3 {
	class GLShapeInstance {
		private:
			GLuint vao;
			GLuint vbo;
			GLuint texture;
			GLuint vertexCount;

		public:
			template <class T> GLShapeInstance(const T&);
			~GLShapeInstance();

			void draw();
			GLuint getTexture(){return texture;}
	};
}

#include "imac2gl3/shapes/GLShapeInstance.tpp"

#endif
