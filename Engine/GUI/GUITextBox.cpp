#include "GUITextBox.h"

#include <cctype>

#include "../Input.h"
#include "../Collision.h"

#include <glfw3.h>

#include "GUIColourRect.h"
#include "GUIText.h"
#include "Font.h"


GUITextBox::GUITextBox(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, GLFWwindow* window, Input* input, Font* font, glm::vec3 dColour, glm::vec3 sColour, std::string acceptedCharacters):GUIBase{position,relativeTo,size,window},input{input},dColour{dColour},sColour{sColour},acceptedCharacters{acceptedCharacters}
{
	float textSize = size.y / font->getHeight();

	background = new GUIColourRect(position, relativeTo, size, window, dColour);	//These 2 GUI elements aren't stored in the GUIManager, text box itself is, so it should be fine
	text = new GUIText(position, relativeTo, { textSize,textSize }, window, "", font, { 1,1,1 });
}

GUITextBox::~GUITextBox()
{
	delete background;
	delete text;
}

void GUITextBox::update()
{
	if(input->getMouseDown(GLFW_MOUSE_BUTTON_1))
	{
		int x, y;
		glfwGetWindowSize(window, &x, &y);

		glm::vec2 mousePos = input->getMousePosition();

		mousePos.y = y - mousePos.y;

		glm::vec2 relativeToTransform = relativeTo / 1024.f;
		relativeToTransform *= glm::vec2{x, y};

		rect collider = { {relativeToTransform + position},{size},0 };
		selected = Collision::checkPointRect(&collider, &mousePos);
	}
	if(selected)
	{
		background->colour = sColour;
		for(int i=0;i<acceptedCharacters.size();i++)
		{
			char c = std::toupper(acceptedCharacters.at(i));
			if(input->getKeyPressed(c))
			{
				std::string curStr = text->getString();
				curStr += c;
				text->generateNewString(curStr);
			}
		}
		if(input->getKeyPressed(GLFW_KEY_BACKSPACE))
		{
			std::string curStr = text->getString();
			if(!curStr.empty())
			{
				curStr.pop_back();
			}
			text->generateNewString(curStr);
		}
	}else
	{
		background->colour = dColour;
	}
}

void GUITextBox::render()
{
	background->render();
	text->render();
}

