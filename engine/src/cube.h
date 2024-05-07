#pragma once

#include<GL\glew.h>
#include<GLFW\glfw3.h>

namespace lowpoly
{



	class cube
	{
	public:
		cube();
		void draw(GLuint shaderProgram);

	public:
		GLuint vertex_array_object;

	private:
		GLuint buf;
		float vertices[36];
	};



}