#include"lowpoly-engine.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

lowpoly_engine::lowpoly_engine()
	: m_GUI{ false }
{
	glfwInit();

    // Hints
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	
	lowpoly_window = glfwCreateWindow(1280, 720, "Lowpoly Engine", NULL, NULL);
	glfwMakeContextCurrent(lowpoly_window);

	glfwSetFramebufferSizeCallback(lowpoly_window, framebuffer_size_callback);


	glewInit();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(lowpoly_window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void lowpoly_engine::processInput()
{
	glfwPollEvents();
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

		

		

		


	// enable GUI render
	if (m_GUI)
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	glfwSwapBuffers(lowpoly_window);
}


void lowpoly_engine::setGUI(bool v)
{
	m_GUI = v;
}