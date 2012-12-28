#define POSITION_LOCATION 0
#define NORMAL_LOCATION 1
#define TEXCOORDS_LOCATION 2

namespace imac2gl3 {
	template <class T> GLShapeInstance::GLShapeInstance(const T& instance){
	
	   	glGenBuffers(1, &vbo);
	   	glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, instance.getByteSize(), instance.getDataPointer(), GL_STATIC_DRAW);
	  	glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &vao);
	    	glBindVertexArray(vao);
	    	glEnableVertexAttribArray(POSITION_LOCATION);
	    	glEnableVertexAttribArray(NORMAL_LOCATION);
	    	glEnableVertexAttribArray(TEXCOORDS_LOCATION);
	    	glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer( POSITION_LOCATION, instance.getPositionNumComponents(),instance.getDataType(),GL_FALSE, instance.getVertexByteSize(), instance.getPositionOffset());
			glVertexAttribPointer(NORMAL_LOCATION, instance.getNormalNumComponents(), instance.getDataType(), GL_FALSE, instance.getVertexByteSize(), instance.getNormalOffset());
			glVertexAttribPointer( TEXCOORDS_LOCATION, instance.getTexCoordsNumComponents(), instance.getDataType(), GL_FALSE, instance.getVertexByteSize(), instance.getTexCoordsOffset());
	   	glBindBuffer(GL_ARRAY_BUFFER, 0);
	   	glBindVertexArray(0);
	 
		vertexCount = instance.getVertexCount();
		texture = instance.getTexture();
	}
}

