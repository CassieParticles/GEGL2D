#pragma once
#include <vector>
#include <string>
#include <functional>

#include <glm.hpp>


struct GLFWwindow;

class GUIBase;		//Forward declare all GUI elements
class GUIColourRect;
class GUITextureRect;
class GUIButton;
class GUIToggleButton;
class GUITextBox;

class Font;
class GUIText;

class Program;
class Input;

class GUIManager
{
public:
	GUIManager(GLFWwindow* window, Input* input);
	~GUIManager();

	void updateWindowSize(glm::ivec2 windowSize) { this->windowSize = windowSize; }

	void render();
	void update();



	//Create functions for all GUI elements
	GUIColourRect* createColourRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, glm::vec3 colour);
	GUITextureRect* createTextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, const std::string& textureDir, glm::vec3 colour);
	GUITextureRect* createTextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, unsigned int textureID, glm::vec3 colour);
	GUIButton* createButton(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, glm::vec3 colour, std::function<void()> func);
	GUIText* createText(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, std::string textString, Font* fontUsed, glm::vec3 colour);
	GUIToggleButton* createToggleButton(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, std::string inactiveFilePath, std::string activeFilePath);
	GUITextBox* createTextBox(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, Font* font, glm::vec3 dColour, glm::vec3 sColour,std::string acceptedCharacters);

	//Generate font class
	Font* createFont(const char* filePath, int height, std::string characterSet);


protected:

	GLFWwindow* window;
	Input* input;

	glm::ivec2 windowSize;

	std::vector<GUIBase*> GUI;
	std::vector<Font*> fonts;

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