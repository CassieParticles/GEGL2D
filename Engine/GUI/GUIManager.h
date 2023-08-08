#pragma once
#include <vector>
#include <string>

#include <glm.hpp>

struct GLFWwindow;

class GUIBase;		//Forward declare all GUI elements
class GUIColourRect;
class GUITextureRect;
class Program;

class GUIManager
{
public:
	GUIManager(GLFWwindow* window);
	~GUIManager();

	void updateWindowSize(glm::ivec2 windowSize) { this->windowSize = windowSize; }

	void render();

	//Create functions for all GUI elements
	GUIColourRect* createColourRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, glm::vec3 colour);
	GUITextureRect* createTextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, const std::string& textureDir, glm::vec3 colour);
	GUITextureRect* createTextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, unsigned int textureID, glm::vec3 colour);

protected:
	GLFWwindow* window;
	glm::ivec2 windowSize;

	std::vector<GUIBase*> GUI;

	unsigned int GUIUBO;	//Uniform buffer for window data

	unsigned int frameBuffer;
	unsigned int frameTexture;

	unsigned int vertexArray;	//buffers and vertex array to store
	unsigned int buffers[2];

	Program* textureProgram;


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