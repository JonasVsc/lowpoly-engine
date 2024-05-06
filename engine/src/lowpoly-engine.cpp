#include"lowpoly-engine.h"

lowpoly_engine::lowpoly_engine()
{
	glfwInit();

    // Hints
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	
	lowpoly_window = glfwCreateWindow(1280, 720, "Lowpoly Engine", NULL, NULL);
	glfwMakeContextCurrent(lowpoly_window);

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

void lowpoly_engine::start()
{
	while (!glfwWindowShouldClose(lowpoly_window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow(); // Show demo window! :)

		glfwPollEvents();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(lowpoly_window);
	}
}

