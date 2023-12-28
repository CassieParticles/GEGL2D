#pragma once
#include <glm.hpp>


/*
	GUI co-ordiantes
		position and size are in pixels, so they don't change when the screen changes size
		relativeTo is a range across the screen, bottomleft is 0,0, topright is 1024,1024

		Position is how many pixels away from relativeTo
*/

class Program;
class BaseLevel;
struct GLFWwindow;

class GUIBase
{
public:
	GUIBase(glm::vec2 position,glm::vec2 relativeTo, glm::vec2 size,Program* renderProgram, BaseLevel* levelIn = nullptr);
	~GUIBase();

	glm::vec2 relativeTo{};	//screen is always 1024x1024 for this, position is in pixels, relative to this point

	glm::vec2 position{};	//TL
	glm::vec2 size{};

	virtual void render() = 0;
	virtual void update() = 0;

	bool draw{ true };

	void setDraw(bool draw) { this->draw = draw; }
protected:
	BaseLevel* levelIn;

	Program* renderProgram{};
	

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