# CMakeList.txt : CMake project for engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("sandbox")

# Packages
find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)



# Add source to this project's executable.
add_executable(sandbox-lowpoly 
	"src/main.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sandbox-lowpoly PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_link_libraries(sandbox-lowpoly PRIVATE glfw)
target_link_libraries(sandbox-lowpoly PRIVATE GLEW::glew)
target_link_libraries(sandbox-lowpoly PRIVATE glm::glm)
target_link_libraries(sandbox-lowpoly PRIVATE imgui::imgui)
target_link_libraries(sandbox-lowpoly PRIVATE lowpoly-engine)

target_include_directories(sandbox-lowpoly PUBLIC "../engine/src")


