#pragma once

#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>

namespace lowpoly
{

void setupUI(GLFWwindow* window);
void renderUI();

}