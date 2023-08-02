#pragma once
#include <glm.hpp>


/*
	GUI co-ordiantes
		Screen is a 1024x1024 area, regardless of actual screen size
		GUI will be drawn to a texture using a frame buffer, this texture can then be drawn to the screen
*/

class Program;
struct GLFWwindow;

class GUIBase
{
public:
	GUIBase(glm::vec2 position, glm::vec2 size, GLFWwindow* window);
	~GUIBase();

	glm::vec2 position{};	//TL
	glm::vec2 size{};

	virtual void render() = 0;

	bool draw{ true };
protected:

	Program* renderProgram{};
	GLFWwindow* window{};

	unsigned int vaoId{};		//VAO and 2 VBOs (position and indices)
	unsigned int vboIds[2]{};

	constexpr static float vertexPos[8] 
	{
		0,0,
		1,0,
		1,1,
		0,1
	};

	constexpr static int indices[6]
	{
		0,2,1,
		0,3,2
	};
};