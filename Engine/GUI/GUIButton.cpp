#include "GUIButton.h"

#include <glfw3.h>

#include "../Input.h"
#include "../Collision.h"
#include "../Window.h"

GUIButton::GUIButton(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, glm::vec3 colour, Input* input, std::function<void()> func) :GUIColourRect{ position,relativeTo,size,colour }, input{ input }, func{ func }
{

}

void GUIButton::update()
{
	if (!input->getMousePressed(GLFW_MOUSE_BUTTON_1)) { return; }
	int x = Window::getWidth();
	int y = Window::getHeight();

	glm::vec2 mousePos = input->getMousePosition();

	mousePos.y = y - mousePos.y;

	glm::vec2 relativeToTransform = relativeTo / 1024.f;
	relativeToTransform *= glm::vec2{x,y};

	rect collider = { {relativeToTransform+position},{size},0 };

	if (Collision::checkPointRect(&collider, &mousePos))
	{
		func();
	}
}
