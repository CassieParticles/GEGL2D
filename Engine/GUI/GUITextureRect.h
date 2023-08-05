#pragma once
#include <string>
#include <glm.hpp>
#include "GUIBase.h"


struct texture;

class GUITextureRect:public GUIBase
{
public:
	GUITextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, GLFWwindow* window, const std::string& textureDir, glm::vec3 colour);
	GUITextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, GLFWwindow* window, unsigned int textureID, glm::vec3 colour);

	~GUITextureRect();

	void render() override;
protected:
	glm::vec3 colour;

	unsigned int texture;
};