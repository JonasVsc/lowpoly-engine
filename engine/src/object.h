#pragma once

#include<GL\glew.h>
#include<GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shader.h"

namespace lowpoly
{
	class object
	{
	public:
		object(shader& s);
		object();

		void draw();
		void set(const char* location_name, glm::mat4 value);
		void set(const char* location_name, glm::vec3 value);
		void set(const char* location_name, float value);
		void setPosition(glm::vec3 pos);

		GLuint vertex_array_object;
	private:
		shader object_shader;
	};



}