#include"lowpoly-engine.h"
#include"config.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main()
{
	
	lowpoly_engine app(lowpoly::SCR_WIDTH, lowpoly::SCR_HEIGHT, "Lowpoly Engine");

	glfwSetFramebufferSizeCallback(app.getWindow(), framebuffer_size_callback);
	glfwSetCursorPosCallback(app.getWindow(), mouse_callback);
	glfwSetInputMode(app.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(app.getWindow(), scroll_callback);

	// Initialize GUI
	// --------------

	// Initialize Shaders & Objects
	// ----------------------------
	shader shader_for_objects("shaders/camera_vs.glsl", "shaders/camera_fs.glsl");
	shader shader_for_lights("shaders/light_vs.glsl", "shaders/light_fs.glsl");

	lowpoly::object cube(shader_for_objects);
	lowpoly::object another_cube(shader_for_objects);
	lowpoly::light light(shader_for_lights);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(app.getWindow()))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = static_cast<float>(glfwGetTime());
		lowpoly::deltaTime = currentFrame - lowpoly::lastFrame;
		lowpoly::lastFrame = currentFrame;

		// input
		// -----
		processInput(app.getWindow());

		// MVP & Settings
		// ---
		
		// model
		glm::mat4 model = glm::mat4(1.0f);
		// view
		glm::mat4 view = lowpoly::camera.GetViewMatrix();
		// projection
		glm::mat4 projection = glm::perspective(glm::radians(lowpoly::camera.Zoom), (float)lowpoly::SCR_WIDTH / lowpoly::SCR_HEIGHT, 0.1f, 100.0f);
		// lightPos
		glm::vec3 light_position = glm::vec3(1.0f, 2.0f, -5.0f);

		// render
		// ------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		// draw
		// ----
		glUseProgram(shader_for_lights.ID);
		lowpoly::model_view_projection(shader_for_lights, model, view, projection);
		light.setPosition(light_position);
		light.draw();


		glUseProgram(shader_for_objects.ID);
		lowpoly::model_view_projection(shader_for_objects, model, view, projection);
		cube.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		cube.set(glm::vec3(0.5f, 0.5f, 1.0f), "objectColor");
		cube.set(glm::vec3(1.0f, 1.0f, 1.0f), "lightColor");
		cube.set(light_position, "lightPos");
		cube.set(lowpoly::camera.Position, "viewPos");
		cube.draw();

		glUseProgram(shader_for_objects.ID);
		lowpoly::model_view_projection(shader_for_objects, model, view, projection);
		another_cube.setPosition(glm::vec3(1.0f, -1.0f, 0.0f));
		another_cube.set(glm::vec3(0.5f, 0.5f, 1.0f), "objectColor");
		another_cube.set(glm::vec3(1.0f, 1.0f, 1.0f), "lightColor");
		another_cube.set(light_position, "lightPos");
		another_cube.draw();
		
		
		// glfw
		// ----
		glfwSwapBuffers(app.getWindow());
		glfwPollEvents();
	}
	
	return 0;
}



// Input handling
// --------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		lowpoly::camera.ProcessKeyboard(FORWARD, lowpoly::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		lowpoly::camera.ProcessKeyboard(BACKWARD, lowpoly::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		lowpoly::camera.ProcessKeyboard(LEFT, lowpoly::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		lowpoly::camera.ProcessKeyboard(RIGHT, lowpoly::deltaTime);
}

// GLFW FUNCTIONS

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (lowpoly::firstMouse)
	{
		lowpoly::lastX = xpos;
		lowpoly::lastY = ypos;
		lowpoly::firstMouse = false;
	}

	float xoffset = xpos - lowpoly::lastX;
	float yoffset = lowpoly::lastY - ypos; // reversed since y-coordinates go from bottom to top

	lowpoly::lastX = xpos;
	lowpoly::lastY = ypos;

	lowpoly::camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	lowpoly::camera.ProcessMouseScroll(static_cast<float>(yoffset));
}