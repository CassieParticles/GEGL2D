#pragma once
#include "GUIBase.h"

#include <string>

#include <glm.hpp>


class Input;

class GUIToggleButton :public GUIBase
{
public:
	GUIToggleButton(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, Input* input, std::string inactiveFilePath, std::string activeFilePath, Program* renderProgram, BaseLevel* levelIn);
	~GUIToggleButton();

	bool getActive() { return active; }

	void update() override;
	void render() override;
protected:
	Input* input;

	int active{};

	unsigned int textures[2];	//0-inactive, 1-active
};