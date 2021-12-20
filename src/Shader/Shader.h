#pragma once

#include <glad/glad.h>
#include <string>
#include <initializer_list>
#include "Vector2.hpp"

class Shader
{
public:
	Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	~Shader();
	void Use();

	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, const Vector2& value);

private:
	GLuint Compile(const std::string& shaderFile, GLenum shaderType);
	void Link(const std::initializer_list<GLuint>& shaders);

private:
	GLuint m_program;
};