// engine.h : Include file for standard system include files,
// or project specific include files.

#pragma once



#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <cstdio>

#include"gui.h"
#include"shader.h"
#include"camera.h"
#include"triangle.h"
#include"object.h"
#include"light.h"
#include"texture.h"


class lowpoly_engine
{
public:
	lowpoly_engine(int width, int height, const char* window_label);

public:
	void setGUI(bool v);
	GLFWwindow* getWindow();

private:


private:
	GLFWwindow* lowpoly_window;
	bool m_GUI;




};

// Utilities
// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// void mouse_callback(GLFWwindow* window, double xpos, double ypos);


// TODO: Reference additional headers your program requires here.
