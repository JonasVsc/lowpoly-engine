#pragma once

#include"lowpoly-engine.h"

namespace lowpoly
{
// Screen size
// -----------
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Camera Settings
// ---------------
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
// ------
float deltaTime = 0.0f;
float lastFrame = 0.0f;
}