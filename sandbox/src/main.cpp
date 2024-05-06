#include"lowpoly-engine.h"

void processInput(GLFWwindow* window);

int main()
{
	lowpoly_engine application;

	application.setGUI(false);

	while (!glfwWindowShouldClose(application.getWindow()))
	{
		application.clear();

		// input
		processInput(application.getWindow());

		// Draw
		

		application.render();
	}
	
	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}