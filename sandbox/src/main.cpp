#include"lowpoly-engine.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


// i will refactor all this into classes, dont worry.
// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

// timing
float delta_time = 0.0f;	// time between current frame and last frame
float last_frame = 0.0f;



int main()
{
	const int screen_width{ 800 };
	const int screen_height{ 600 };
	lowpoly_engine app(800, 600, "Lowpoly Engine");

	glfwSetFramebufferSizeCallback(app.getWindow(), framebuffer_size_callback);
	glfwSetCursorPosCallback(app.getWindow(), mouse_callback);
	glfwSetInputMode(app.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GUI
	// --------------
	// lowpoly::setupUI(app.getWindow());

	// Shaders
	// -------
	shader s1("shaders/vertexShader.vs", "shaders/fragmentShader.fs");
	shader s2("shaders/camera_vs.glsl", "shaders/camera_fs.glsl");


	// Objects
	// -------
	lowpoly::cube c1;


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
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.4f, 1.0f));
		// view
		glm::mat4 view;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
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
		c1.draw(s2.ID);
		

		// render UI
		// ---------
		// lowpoly::renderUI();

		// glfw
		// ----
		glfwSwapBuffers(app.getWindow());
		glfwPollEvents();
	}
	
	return 0;
}


void processInput(GLFWwindow* window)
{

	double current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
	float camera_speed = static_cast<float>( 2.5 * delta_time );

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += camera_speed * cameraFront;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= camera_speed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * camera_speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += camera_speed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		cameraPos -= camera_speed * cameraUp;
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

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}