#include"lowpoly-engine.h"

lowpoly_engine::lowpoly_engine()
{

	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	lowpoly_window = glfwCreateWindow(1280, 720, "Lowpoly Engine", NULL, NULL);
	
	glfwInit();

	glfwMakeContextCurrent(lowpoly_window);

	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

