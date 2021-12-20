#pragma once

#include <glad/glad.h>

class VBO 
{
public:
	VBO(const GLfloat* vertices, GLsizeiptr size);
	~VBO();

	void Bind();
	void UnBind();


private:
	GLuint m_buffer;
};