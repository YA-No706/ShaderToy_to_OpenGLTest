#pragma once

#include <glad/glad.h>
#include "VBO/VBO.h"

class VAO
{
public:
	VAO();
	~VAO();

	void LinkAttribute(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void UnBind();


private:
	GLuint m_buffer;
};