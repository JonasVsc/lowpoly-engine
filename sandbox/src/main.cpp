#include"lowpoly-engine.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void MVP(shader &s);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	
	lowpoly_engine app(SCR_WIDTH, SCR_HEIGHT, "Lowpoly Engine");

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
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(app.getWindow());

		// MVP & Settings
		// ---
		
		// model
		glm::mat4 model = glm::mat4(1.0f);
		// view
		glm::mat4 view = camera.GetViewMatrix();
		// projection
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		// lightPos
		glm::vec3 light_position = glm::vec3(1.0f, 2.0f, -5.0f);

		// render
		// ------
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		// draw
		// ----
		glUseProgram(shader_for_lights.ID);
		glUniformMatrix4fv(glGetUniformLocation(shader_for_lights.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader_for_lights.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader_for_lights.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		light.setPosition(light_position);
		light.draw();


		glUseProgram(shader_for_objects.ID);
		glUniformMatrix4fv(glGetUniformLocation(shader_for_objects.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader_for_objects.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader_for_objects.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		cube.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		cube.set(glm::vec3(0.5f, 0.5f, 1.0f), "objectColor");
		cube.set(glm::vec3(1.0f, 1.0f, 1.0f), "lightColor");
		cube.set(light_position, "lightPos");
		cube.set(camera.Position, "viewPos");
		cube.draw();

		glUseProgram(shader_for_objects.ID);
		glUniformMatrix4fv(glGetUniformLocation(shader_for_objects.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader_for_objects.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader_for_objects.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
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
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
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

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}