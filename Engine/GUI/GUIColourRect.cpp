#include "GUIColourRect.h"

#include <glad/glad.h>
#include <glfw3.h>

#include "../Program.h"

GUIColourRect::GUIColourRect(glm::vec2 position, glm::vec2 size, GLFWWindow* window, glm::vec3 colour) :GUIBase(position, size, window), colour{ colour }
{
	renderProgram = new Program(vertexShaderCode, fragmentShaderCode, Program::sourceCode);

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(2, vboIds);

	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

GUIColourRect::~GUIColourRect()
{
}

void GUIColourRect::render()
{
	if (!draw) { return; }
	glBindVertexArray(vaoId);

	renderProgram->use();

	renderProgram->setVec2("position", position);
	renderProgram->setVec2("size", size);

	renderProgram->setVec3("colour", colour);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
