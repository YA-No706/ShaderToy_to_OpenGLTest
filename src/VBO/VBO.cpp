#include "VBO.h"

VBO::VBO(const GLfloat* vertices, GLsizeiptr size)
	: m_buffer(0)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &m_buffer);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
}

void VBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
