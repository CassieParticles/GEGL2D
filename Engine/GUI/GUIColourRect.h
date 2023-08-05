#pragma once
#include "GUIBase.h"

#include <string>

class GUIColourRect : public GUIBase
{
public:
	GUIColourRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, GLFWwindow* window, glm::vec3 colour);
	~GUIColourRect();

	void render() override;

	void setWindow(GLFWwindow* window);
protected:
	glm::vec3 colour;
};