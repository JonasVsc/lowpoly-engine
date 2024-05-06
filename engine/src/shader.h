#pragma once

#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include<fstream>
#include<sstream>
#include<iostream>


namespace lowpoly
{

class shader
{
public:
	shader(const char *vertex_path, const char *fragment_path);
	static const char* read_file(const char* p_shader_file_path);

public:
	GLuint program;
	GLuint vertex_shader;
	GLuint fragment_shader;

private:
	static void catch_shader_compile_errors(GLuint shader);
	static void catch_program_compile_errors(GLuint program);


};




}

