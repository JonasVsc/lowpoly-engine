#include"lowpoly-engine.h"


lowpoly_engine::lowpoly_engine()
	: m_GUI{ false }
{
	glfwInit();

    // Window Hints
	// glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	
	lowpoly_window = glfwCreateWindow(800, 600, "Lowpoly Engine", NULL, NULL);
	glfwMakeContextCurrent(lowpoly_window);

	glfwSetFramebufferSizeCallback(lowpoly_window, framebuffer_size_callback);

	glewInit();

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

	
	glfwSwapBuffers(lowpoly_window);
	glfwPollEvents();
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