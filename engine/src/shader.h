#pragma once

#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include<fstream>
#include<sstream>
#include<iostream>




class shader
{
public:
	shader(const char *vertex_path, const char *fragment_path);
	void use();
	GLuint ID;
private:
	void check_compile_errors(unsigned int shader, std::string type);



};