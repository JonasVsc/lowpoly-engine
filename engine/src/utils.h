#pragma once

#include"shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace lowpoly
{


	void model_view_projection(shader& s, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);


}