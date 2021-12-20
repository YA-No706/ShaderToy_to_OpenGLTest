#pragma once

#include <glad/glad.h>

class EBO 
{
public:
	EBO(const GLuint* indices, GLsizeiptr size);
	~EBO();

	void Bind();
	void UnBind();


private:
	GLuint m_buffer;
};