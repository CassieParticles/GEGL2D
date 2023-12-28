#include "GUIToggleButton.h"

#include <glad/glad.h>
#include <glfw3.h>

#include "../TextureManager.h"
#include "../Program.h"
#include "../Collision.h"
#include "../Input.h"
#include "../Window.h"

GUIToggleButton::GUIToggleButton(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, Input* input, std::string inactiveFilePath, std::string activeFilePath):GUIBase{position,relativeTo,size},input{input}
{
	textures[0] = TextureManager::getTexturePtr(inactiveFilePath).textureID;
	textures[1] = TextureManager::getTexturePtr(activeFilePath).textureID;

	renderProgram = new Program("Engine/Shaders/GUITextureRect.vert", "Engine/Shaders/GUITextureRect.frag",Program::filePath);
}

GUIToggleButton::~GUIToggleButton()
{
}

void GUIToggleButton::update()
{
	if (!draw) { return; }
	if (!input->getMousePressed(GLFW_MOUSE_BUTTON_1)) { return; }
	int x = Window::getWidth();
	int y = Window::getHeight();

	glm::vec2 mousePos = input->getMousePosition();

	mousePos.y = y - mousePos.y;

	glm::vec2 relativeToTransform = relativeTo / 1024.f;
	relativeToTransform *= glm::vec2{x, y};

	rect collider = { {relativeToTransform + position},{size},0 };

	if (Collision::checkPointRect(&collider, &mousePos))
	{
		active = 1 - active;
	}
}

void GUIToggleButton::render()
{
	if (!draw) { return; }
	glBindVertexArray(vaoId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[active]);

	renderProgram->use();

	renderProgram->setVec2("position", position);
	renderProgram->setVec2("size", size);
	renderProgram->setVec2("relativeTo", relativeTo);

	renderProgram->setVec3("colour", {1,1,1});
	renderProgram->setInt("tex", 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
