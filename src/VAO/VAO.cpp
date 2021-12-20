#include "VAO.h"

VAO::VAO()
	: m_buffer(0)
{
	glGenVertexArrays(1, &m_buffer);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &m_buffer);
}

void VAO::LinkAttribute(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.UnBind();
}

void VAO::Bind()
{
	glBindVertexArray(m_buffer);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}
