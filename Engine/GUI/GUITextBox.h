#pragma once
#include "GUIBase.h"

#include <string>

class GUIColourRect;
class GUIText;
class Input;
class Font;

class GUITextBox:public GUIBase
{
public:
	GUITextBox(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size,Input* input,Font* font, glm::vec3 dColour, glm::vec3 sColour, std::string acceptedCharacters, Program* renderProgramBox,Program* renderProgramText, BaseLevel* levelIn);
	~GUITextBox();

	void update() override;
	void render() override;

	GUIText* getTextPtr() { return text; }		//For adjusting text and background sizes
	GUIColourRect* getBgPtr() { return background; }
protected:
	bool selected{};

	bool firstCharacter{};

	Input* input;

	GUIColourRect* background;
	GUIText* text;

	std::string acceptedCharacters;

	glm::vec3 dColour;
	glm::vec3 sColour;
};