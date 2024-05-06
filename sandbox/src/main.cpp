#include"lowpoly-engine.h"

void processInput(GLFWwindow* window);



int main()
{
	lowpoly_engine application;

	// settings
	application.setGUI(false);

	//shader
	lowpoly::shader my_shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

	// objects
	lowpoly::triangle t;
	
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);



	while (!glfwWindowShouldClose(application.getWindow()))
	{
		// input
		processInput(application.getWindow());

		application.clear();

		// Shader
		glUseProgram(my_shader.program);
		t.draw();
		

		// Render
		application.render();
	}
	
	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}