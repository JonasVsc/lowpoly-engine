#pragma once

#include<GL\glew.h>
#include<GLFW\glfw3.h>


#include<iostream>



namespace lowpoly
{

class texture
{
public:
	texture(GLuint program, const char* texture_path);
	GLuint texture_;
private:

};


}
