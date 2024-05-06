#include"lowpoly-engine.h"

void processInput(GLFWwindow* window);



int main()
{
	lowpoly_engine app;

	// Shaders
	// -------
	shader s1("shaders/vertexShader.vs", "shaders/fragmentShader.fs");


	// Objects
	// -------
	lowpoly::triangle t1;


	// render loop
	// -----------
	while (!glfwWindowShouldClose(app.getWindow()))
	{
		// input
		// -----
		processInput(app.getWindow());

		// render
		// ------
		glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// draw triangle
		// -------------
		t1.draw(s1.ID);

		// glfw
		// ----
		glfwSwapBuffers(app.getWindow());
		glfwPollEvents();
	}
	
	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}