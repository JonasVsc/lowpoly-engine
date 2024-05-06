#include"lowpoly-engine.h"

void processInput(GLFWwindow* window);

int main()
{
	lowpoly_engine application;

	// settings
	application.setGUI(false);


	// shaders
	lowpoly::shader my_shader("shaders/vertexShader.vs", "shaders/fragmentShader.fs");

	while (!glfwWindowShouldClose(application.getWindow()))
	{
		application.clear();

		// input
		processInput(application.getWindow());

		// Draw

		
		glUseProgram(my_shader.program);
		application.render();
	}
	
	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}