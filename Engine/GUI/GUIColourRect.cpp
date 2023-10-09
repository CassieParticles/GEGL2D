#include "GUIColourRect.h"
#include "GUIColourRect.h"

#include <glad/glad.h>
#include <glfw3.h>

#include "../Program.h"
#include "../Window.h"

GUIColourRect::GUIColourRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, glm::vec3 colour) :GUIBase(position,relativeTo, size), colour{ colour }
{
	renderProgram = new Program("Engine/Shaders/GUI/GUIColourRect.vert", "Engine/Shaders/GUI/GUIColourRect.frag", Program::filePath);

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

	int x=Window::getWidth();
	int y=Window::getHeight();

	renderProgram->setVec2("position", position);
	renderProgram->setVec2("size", size);
	renderProgram->setVec2("relativeTo", relativeTo);

	renderProgram->setVec3("colour", colour);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
