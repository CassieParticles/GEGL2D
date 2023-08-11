#include "GUIColourRect.h"
#include "GUIColourRect.h"

#include <glad/glad.h>
#include <glfw3.h>

#include "../Program.h"

GUIColourRect::GUIColourRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, GLFWwindow* window, glm::vec3 colour) :GUIBase(position,relativeTo, size, window), colour{ colour }
{
	renderProgram = new Program("Engine/Shaders/GUIColourRect.vert", "Engine/Shaders/GUIColourRect.frag", Program::filePath);

	renderProgram->setUniformBufferBlockBinding("windowData", 0);

}

GUIColourRect::~GUIColourRect()
{
}

void GUIColourRect::render()
{
	if (!draw) { return; }
	glBindVertexArray(vaoId);

	renderProgram->use();

	int x;
	int y;
	
	glfwGetWindowSize(window, &x, &y);

	renderProgram->setVec2("position", position);
	renderProgram->setVec2("size", size);
	renderProgram->setVec2("relativeTo", relativeTo);

	renderProgram->setVec3("colour", colour);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GUIColourRect::setWindow(GLFWwindow* window)
{
	this->window = window;
}
