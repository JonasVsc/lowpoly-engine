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

		void draw();
		void set(glm::vec3 color, const char* location_name);
		void setPosition(glm::vec3 pos);

	private:
		GLuint vertex_array_object;
		shader object_shader;
	};



}