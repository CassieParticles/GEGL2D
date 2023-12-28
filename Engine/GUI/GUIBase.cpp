#include "GUIBase.h"

#include <iostream>
#include <glad/glad.h>

#include "../Program.h"
#include "../GameObjects/GameObjects.h"

GUIBase::GUIBase(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size):position{position},relativeTo{relativeTo}, size{size}
{
	GameObjects::genTextureSquare(&vaoId, vboIds + 0, vboIds + 1);	//Create data

	glBindVertexArray(0);
}

GUIBase::~GUIBase()
{
	delete renderProgram;

	glDeleteBuffers(2, vboIds);
	glDeleteVertexArrays(1, &vaoId);
}
