#include "GUITextBox.h"

#include <cctype>

#include "../Input.h"
#include "../Collision.h"
#include "../Window.h"
#include "../BaseLevel.h"

#include <glfw3.h>

#include "GUIColourRect.h"
#include "GUIText.h"
#include "Font.h"


GUITextBox::GUITextBox(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size,  Input* input, Font* font, glm::vec3 dColour, glm::vec3 sColour, std::string acceptedCharacters, Program* renderProgramBox, Program* renderProgramText, BaseLevel* levelIn):GUIBase{position,relativeTo,size,nullptr,levelIn},input{input},dColour{dColour},sColour{sColour},acceptedCharacters{acceptedCharacters}
{
	float textSize = size.y / font->getHeight();

	background = new GUIColourRect(position, relativeTo, size, dColour,renderProgramBox,levelIn);	//These 2 GUI elements aren't stored in the GUIManager, text box itself is, so it should be fine
	text = new GUIText(position + glm::vec2{0,5}, relativeTo, { textSize,textSize }, "", font, { 1,1,1 }, renderProgramText, levelIn,-1,size.x);
}

GUITextBox::~GUITextBox()
{
	delete background;
	delete text;
}

void GUITextBox::update()
{
	if (!draw) { return; }

	if (levelIn)
	{
		if (!levelIn->isOpen())	//If the level the GUI is in is closed, exit early
		{
			return;
		}
	}

	if(input->getMouseDown(GLFW_MOUSE_BUTTON_1))
	{
		int x = Window::getWidth();
		int y = Window::getHeight();

		glm::vec2 mousePos = input->getMousePosition();

		mousePos.y = y - mousePos.y;

		glm::vec2 relativeToTransform = relativeTo / 1024.f;
		relativeToTransform *= glm::vec2{x, y};

		rect collider = { {relativeToTransform + position},{size},0 };
		selected = Collision::checkPointRect(&collider, &mousePos);
		firstCharacter = selected;
	}
	if(selected)
	{
		background->colour = sColour;
		for(int i=0;i<acceptedCharacters.size();i++)
		{
			char c = std::toupper(acceptedCharacters.at(i));
			if(input->getKeyPressed(c))
			{
				firstCharacter = { false };
				std::string curStr = text->getString();
				curStr += c;
				text->generateNewString(curStr);
			}
		}
		if(input->getKeyPressed(GLFW_KEY_BACKSPACE))
		{
			
			if(firstCharacter)
			{
				text->generateNewString("");
				firstCharacter = { false };
			}
			else
			{
				std::string curStr = text->getString();
				if (!curStr.empty())
				{
					curStr.pop_back();
				}
				text->generateNewString(curStr);
			}
		}
	}else
	{
		background->colour = dColour;
	}
}

void GUITextBox::render()
{
	if (!draw) { return; }

	if (levelIn)
	{
		if (!levelIn->isOpen())	//If the level the GUI is in is closed, exit early
		{
			return;
		}
	}

	background->render();
	text->render();
}

