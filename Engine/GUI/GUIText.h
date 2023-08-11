#pragma once
#include "GUIBase.h"
#include <glm.hpp>

class Font;
struct character;

class GUIText:public GUIBase
{
public:
	GUIText(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, GLFWwindow* window, char* string, int stringLength, Font* fontUsed, glm::vec3 colour);
	~GUIText();

	void generateNewString(char* newString, int newStringLength);

	void render() override;
	void update() override {};
protected:
	char* string{};
	int stringLength{};

	Font* font;

	character* characterArray{};

	glm::vec3 colour;
};