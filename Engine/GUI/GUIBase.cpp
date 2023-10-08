#include "GUIBase.h"

#include <iostream>
#include <glad/glad.h>

#include "../Program.h"

GUIBase::GUIBase(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size):position{position},relativeTo{relativeTo}, size{size}
{
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(2, vboIds);

	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

GUIBase::~GUIBase()
{
	delete renderProgram;

	glDeleteBuffers(2, vboIds);
	glDeleteVertexArrays(1, &vaoId);
}
