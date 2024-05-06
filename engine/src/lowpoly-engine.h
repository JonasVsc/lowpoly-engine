// engine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

#include <iostream>
#include <cstdio>

class lowpoly_engine
{
public:
	lowpoly_engine();


public:
	void start();






private:
	GLFWwindow* lowpoly_window;




};



// TODO: Reference additional headers your program requires here.
