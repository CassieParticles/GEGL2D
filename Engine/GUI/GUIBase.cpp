#include "GUIBase.h"

#include <iostream>
#include <glad/glad.h>

#include "../Program.h"
#include "../GameObjects/GameObjects.h"

GUIBase::GUIBase(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, Program* renderProgram, BaseLevel* levelIn):position{position},relativeTo{relativeTo}, size{size},renderProgram{renderProgram}, levelIn{levelIn}
{
	GameObjects::genTextureSquare(&vaoId, vboIds + 0, vboIds + 1);	//Create data

	glBindVertexArray(0);
}

GUIBase::~GUIBase()
{
	glDeleteBuffers(2, vboIds);
	glDeleteVertexArrays(1, &vaoId);
}
