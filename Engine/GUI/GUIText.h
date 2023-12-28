#pragma once

#include "GUIBase.h"
#include <glm.hpp>
#include <string>

class Font;
struct character;

class GUIText:public GUIBase
{
public:
	GUIText(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, std::string textString, Font* fontUsed, glm::vec3 colour, Program* renderProgram, BaseLevel* levelIn, int characterLimit=-1,int pixelLimit=-1);
	~GUIText();

	void generateNewString(std::string newString);

	std::string getString() { return textString; }

	void render() override;
	void update() override {};
protected:
	std::string textString{};

	Font* font;

	character* characterArray{};

	int characterLimit;
	int pixelLimit;

	glm::vec3 colour;
};