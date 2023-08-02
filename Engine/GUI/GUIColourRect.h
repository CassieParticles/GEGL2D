#pragma once
#include "GUIBase.h"

#include <string>

class GUIColourRect : public GUIBase
{
public:
	GUIColourRect(glm::vec2 position, glm::vec2 size, GLFWWindow* window, glm::vec3 colour);
	~GUIColourRect();

	void render() override;
protected:
	glm::vec3 colour;

private:
	//Vertex shader code directly
	const std::string vertexShaderCode = "\n\
\n\
#version 330 core\n\
\n\
layout(location = 0) in vec2 vertexPosition;\n\
\n\
uniform vec2 position;\n\
uniform vec2 size;\n\
\n\
void main()\n\
{\n\
	vec2 tl = vec2(position.x/1024,position.y/1024);	//Get the position from 0-1\n\
	vec2 offset = vec2(size.x*vertexPosition.x/1024,size.y*vertexPosition.y/1024);\n\
\n\
	//tl *= 2;	//rescale to be between -1 - 1\n\
	//offset = offset * 2;\n\
\n\
	gl_Position = vec4(tl + offset, 0, 1);\n\
}\n";

	//Fragment shader code
	const std::string fragmentShaderCode = "\n\
#version 330 core\n\
\n\
uniform vec3 colour;\n\
\n\
out vec4 outColour;\n\
\n\
void main()\n\
{\n\
	outColour = vec4(colour, 1);\n\
}";
};