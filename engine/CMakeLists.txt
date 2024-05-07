# CMakeList.txt : CMake project for engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project("engine")

# Packages
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)


# Add source to this project's executable.
add_library(lowpoly-engine STATIC 
	"src/lowpoly-engine.cpp" 
	"src/lowpoly-engine.h"
	"src/triangle.cpp"
	"src/triangle.h" 
	"src/shader.cpp"
	"src/shader.h"
	"src/gui.h"
	"src/gui.cpp"
	"src/camera.h"
	"src/cube.h"
	"src/cube.cpp"
	"src/stb_image.h"
	"src/texture.h"
	"src/texture.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lowpoly-engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

target_link_libraries(lowpoly-engine PRIVATE glfw)
target_link_libraries(lowpoly-engine PRIVATE GLEW::glew)
target_link_libraries(lowpoly-engine PRIVATE glm::glm)
target_link_libraries(lowpoly-engine PRIVATE imgui::imgui)

