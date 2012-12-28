#include <iostream>
#include <cstdlib>
#include <cstddef>
#include "imac2gl3/shapes/GLShapeInstance.hpp"

#define POSITION_LOCATION 0
#define NORMAL_LOCATION 1
#define TEXCOORDS_LOCATION 2

namespace imac2gl3 {

	GLShapeInstance::~GLShapeInstance(){
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
	}

	void GLShapeInstance::draw(){
		 glBindVertexArray(vao);
		       glDrawArrays(GL_TRIANGLES, 0, vertexCount); 
		glBindVertexArray(0);
	}
}

