#include"lowpoly-engine.h"

void processInput(GLFWwindow* window);



int main()
{
	const int screen_width{ 800 };
	const int screen_height{ 600 };
	lowpoly_engine app(800, 600, "Lowpoly Engine");

	// Initialize GUI
	// --------------
	lowpoly::setupUI(app.getWindow());

	// Shaders
	// -------
	shader s1("shaders/vertexShader.vs", "shaders/fragmentShader.fs");
	shader s2("shaders/camera_vs.glsl", "shaders/camera_fs.glsl");


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

		// MVP
		// ---

		// model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		// view
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		// projection
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		// locations
		glUniformMatrix4fv(glGetUniformLocation(s2.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(s2.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(s2.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// render
		// ------
		glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// draw triangle
		// -------------
		t1.draw(s2.ID);

		// render UI
		// ---------
		lowpoly::renderUI();

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