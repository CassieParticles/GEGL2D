#pragma once
#include "GUIColourRect.h"

class Input;

#include <functional>

class GUIButton:public GUIColourRect
{
public:
	GUIButton(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, glm::vec3 colour, Input* input, std::function<void()> func, Program* renderProgram, BaseLevel* levelIn);
	~GUIButton();

	void update() override;
protected:
	std::function<void()> func;
	Input* input;
};