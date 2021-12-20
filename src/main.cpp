#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader/Shader.h"
#include "VAO/VAO.h"
#include "VBO/VBO.h"
#include "EBO/EBO.h"
#include "Vector2.hpp"

void Error_GLFW_Callback(int error, const char* description)
{
	std::cout << "GLFW ERROR : " << description << std::endl;
}

const int WindowWidth = 640;
const int WindowHeight = 360;

const GLfloat vertices[] = {
	/*-------POSITION-----I----UV------*/
	-1.0f,  -1.0f, 0.0f,	0.0f,0.0f,
	-1.0f,   1.0f, 0.0f,	0.0f,1.0f,
	 1.0f,   1.0f, 0.0f,	1.0f,1.0f,
	 1.0f,  -1.0f, 0.0f,	1.0f,0.0f
};
const GLuint indices[] = {
	0,2,1,
	0,3,2
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(WindowWidth, WindowHeight, "Shadertoy -> OpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(Error_GLFW_Callback);
	glfwSwapInterval(1);

	gladLoadGL();

	Shader shader("Shader/sample.vert", "Shader/sample.frag");

	VAO vao;
	vao.Bind();
	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));
	//POSITION layout = 0
	vao.LinkAttribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);
	//TEXCOORD layout = 1
	vao.LinkAttribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vao.UnBind();
	vbo.UnBind();
	ebo.UnBind();

	glViewport(0, 0, WindowWidth, WindowHeight);
	while (!glfwWindowShouldClose(window))
	{
		//----Update----
		//iTime
		float currentFrame = glfwGetTime();

		//----Render----
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Use();
		shader.SetUniform("iResolution", { WindowWidth, WindowHeight });
		shader.SetUniform("iTime", currentFrame);
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT , 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}