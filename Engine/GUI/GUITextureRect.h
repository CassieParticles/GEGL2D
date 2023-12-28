#pragma once
#include <string>
#include <glm.hpp>
#include "GUIBase.h"


struct texture;

class GUITextureRect:public GUIBase
{
public:
	GUITextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, const std::string& textureDir, glm::vec3 colour, Program* renderProgram, BaseLevel* levelIn);
	GUITextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, unsigned int textureID, glm::vec3 colour, Program* renderProgram, BaseLevel* levelIn);

	~GUITextureRect();

	void render() override;
	void update() override{};

protected:
	glm::vec3 colour;

	unsigned int texture;
};