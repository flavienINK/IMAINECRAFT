#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <cstddef>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "imac2gl3/shader_tools.hpp"

class MatrixStack{
	private:
		std::stack<glm::mat4> m_Stack;

	public:
		MatrixStack();
		~MatrixStack();
		void push();
		void pop();
		void mult(const glm::mat4&);
		const glm::mat4& top() const;
		void set(const glm::mat4&);
		void scale(const glm::vec3&);
		void translate(const glm::vec3&);
		void rotate(float, const glm::vec3&);
};

#endif