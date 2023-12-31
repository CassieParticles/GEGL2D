#include "GUITextureRect.h"

#include <glad/glad.h>
#include <glfw3.h>

#include "../TextureManager.h"
#include "../Program.h"
#include "../BaseLevel.h"

GUITextureRect::GUITextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, const std::string& textureDir, glm::vec3 colour, Program* renderProgram, BaseLevel* levelIn):GUIBase{position,relativeTo,size,renderProgram,levelIn},colour{colour}
{
	//renderProgram = new Program("Engine/Shaders/GUI/GUITextureRect.vert", "Engine/Shaders/GUI/GUITextureRect.frag", Program::filePath);

	renderProgram->setUniformBufferBlockBinding("windowData", 0);

	texture = TextureManager::getTexturePtr(textureDir).textureID;
}

GUITextureRect::GUITextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, unsigned int textureID, glm::vec3 colour, Program* renderProgram, BaseLevel* levelIn) :GUIBase{ position,relativeTo,size,renderProgram,levelIn }, colour{ colour },texture { textureID }
{
	//renderProgram = new Program("Engine/Shaders/GUI/GUITextureRect.vert", "Engine/Shaders/GUI/GUITextureRect.frag", Program::filePath);

	renderProgram->setUniformBufferBlockBinding("windowData", 0);
}

GUITextureRect::~GUITextureRect()
{
}

void GUITextureRect::render()
{
	if (!draw) { return; }	//Don't do anything if the GUI shouldn't be drawn

	if (levelIn)
	{
		if (!levelIn->isOpen())	//If the level the GUI is in is closed, exit early
		{
			return;
		}
	}

	glBindVertexArray(vaoId);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	renderProgram->use();

	renderProgram->setVec2("position", position);
	renderProgram->setVec2("size", size);
	renderProgram->setVec2("relativeTo", relativeTo);

	renderProgram->setVec3("colour", colour);
	renderProgram->setInt("tex", 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
