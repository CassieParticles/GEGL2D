#pragma once
#include "GUIBase.h"
#include <glm.hpp>
#include <string>

class Font;
struct character;

class GUIText:public GUIBase
{
public:
	GUIText(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, GLFWwindow* window, std::string textString, Font* fontUsed, glm::vec3 colour);
	~GUIText();

	void generateNewString(std::string newString);

	void render() override;
	void update() override {};
protected:
	std::string textString;

	Font* font;

	character* characterArray{};

	glm::vec3 colour;
};