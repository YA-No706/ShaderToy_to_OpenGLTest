#include "Shader.h"
#include "Utility/File.hpp"
#include <iostream>

Shader::Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	: m_program(0)
{
	GLuint vertexShader = Compile(vertexShaderFile, GL_VERTEX_SHADER);
	GLuint fragmentShader = Compile(fragmentShaderFile, GL_FRAGMENT_SHADER);
	Link({ vertexShader, fragmentShader });
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

void Shader::Use()
{
	glUseProgram(m_program);
}

void Shader::SetUniform(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, const Vector2& value)
{
	glUniform2f(glGetUniformLocation(m_program, name.c_str()), value.x, value.y);
}

GLuint Shader::Compile(const std::string& shaderFile, GLenum shaderType)
{
	std::string source = File::GetFileContents(shaderFile);
	const GLchar* source_char = source.c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source_char, nullptr);
	glCompileShader(shader);

	GLint status;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "Error " << shaderFile <<" compile failed\n" << infoLog << std::endl;
	}

	return shader;
}

void Shader::Link(const std::initializer_list<GLuint>& shaders)
{
	m_program = glCreateProgram();
	for (auto shader : shaders)
	{
		glAttachShader(m_program, shader);
	}
	glLinkProgram(m_program);
	for (auto shader : shaders)
	{
		glDetachShader(m_program, shader);
		glDeleteShader(shader);
	}

	GLint result;
	GLchar infoLog[512];
	glGetProgramiv(m_program, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
		std::cout << "Error shader link failed\n" << infoLog << std::endl;
	}
}
