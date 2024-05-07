﻿#include"lowpoly-engine.h"


lowpoly_engine::lowpoly_engine(int width, int height, const char* window_label)
	: m_GUI{ false }
{
	if (!glfwInit())
		std::cerr << "Error::glfw::init";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	lowpoly_window = glfwCreateWindow(width, height, window_label, NULL, NULL);
	glfwMakeContextCurrent(lowpoly_window);

	glfwSetFramebufferSizeCallback(lowpoly_window, framebuffer_size_callback);

	if (glewInit() != GLEW_OK)
		std::cerr << "Error::glew::init";

	printf("gl version: %s\n", glGetString(GL_VERSION));
}


void lowpoly_engine::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void lowpoly_engine::draw()
{
}


void lowpoly_engine::render()
{

	
	
}


void lowpoly_engine::setGUI(bool v)
{
	m_GUI = v;
}

GLFWwindow* lowpoly_engine::getWindow()
{
	return lowpoly_window;
}



// GLFW FUNCTIONS

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}