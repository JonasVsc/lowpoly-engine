#include"lowpoly-engine.h"
#include"config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path);

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


	// texture
	// -------
	std::string texture_path = "textures/container2.png";
	GLuint diffuseMap = loadTexture("textures/container2.png");
	glUseProgram(shader_for_objects.ID);
	cube.set("material.diffuse", 0);


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

		// Settings
		// --------
		
		

		

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

		


		glUseProgram(shader_for_objects.ID);
		cube.set("light.position", lowpoly::lightPos);
		cube.set("viewPos", lowpoly::camera.Position);

		// light properties
		cube.set("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		cube.set("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		cube.set("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		// material properties
		cube.set("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		cube.set("material.shininess", 64.0f);

		// view/projection transformations
		lowpoly::model_view_projection(shader_for_objects, model, view, projection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		cube.draw();


		cube.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		cube.set("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		cube.set("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		cube.set("lightPos", light_position);
		cube.set("viewPos", lowpoly::camera.Position);

		
		// draw
		// ----
		glUseProgram(shader_for_lights.ID);
		model = glm::translate(model, lowpoly::lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lowpoly::model_view_projection(shader_for_lights, model, view, projection);
		light.draw();
		
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

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}