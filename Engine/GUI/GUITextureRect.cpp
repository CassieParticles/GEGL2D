#include "GUITextureRect.h"

#include <glad/glad.h>
#include <glfw3.h>

#include "../TextureManager.h"
#include "../Program.h"

GUITextureRect::GUITextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, GLFWwindow* window, const std::string& textureDir, glm::vec3 colour):GUIBase{position,relativeTo,size,window},colour{colour}
{
	texture = TextureManager::getTexturePtr(textureDir).textureID;

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

	renderProgram = new Program("Engine/Shaders/GUITextureRect.vert", "Engine/Shaders/GUITextureRect.frag", Program::filePath);
}

GUITextureRect::GUITextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, GLFWwindow* window, unsigned int textureID, glm::vec3 colour) :GUIBase{ position,relativeTo,size,window }, colour{ colour },texture { textureID }
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

	renderProgram = new Program("Engine/Shaders/GUITextureRect.vert", "Engine/Shaders/GUITextureRect.frag", Program::filePath);
}

GUITextureRect::~GUITextureRect()
{
}

void GUITextureRect::render()
{
	if (!draw) { return; }	//Don't do anything if the GUI shouldn't be drawn

	glBindVertexArray(vaoId);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	int x;
	int y;

	glfwGetWindowSize(window, &x, &y);

	renderProgram->use();

	renderProgram->setVec2("position", position);
	renderProgram->setVec2("size", size);
	renderProgram->setVec2("screenSize", glm::vec2{x, y});
	renderProgram->setVec2("relativeTo", relativeTo);

	renderProgram->setVec3("colour", colour);
	renderProgram->setInt("tex", 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
