#include "BaseLevel.h"

#include <glad/glad.h>
#include <glfw3.h>

#include "Input.h"
#include "Window.h"

BaseLevel::BaseLevel( Input* input, GUIManager* guiManager, glm::vec4 bgColour) :input{ input }, guiManager{ guiManager }, bgColour{ bgColour }
{
}

void BaseLevel::openLevel() 
{
	glClearColor(bgColour.r,bgColour.g,bgColour.b,bgColour.a);
}

void BaseLevel::closeLevel() {}

BaseLevel::~BaseLevel() {}

void BaseLevel::beginDraw()
{
	glClearColor(bgColour.r, bgColour.g, bgColour.b, bgColour.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BaseLevel::endDraw()
{
	glfwSwapBuffers(Window::getWindow());	//Check and call events
}
