#pragma once
#include <vector>
#include <string>

#include <glm.hpp>

struct GLFWwindow;

class GUIBase;		//Forward declare all GUI elements
class GUIColourRect;
class GUITextureRect;

class GUIManager
{
public:
	GUIManager(GLFWwindow* window);
	~GUIManager();

	void render();

	//Create functions for all GUI elements
	GUIColourRect* createColourRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, glm::vec3 colour);
	GUITextureRect* createTextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, const std::string& textureDir, glm::vec3 colour);
	GUITextureRect* createTextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, unsigned int textureID, glm::vec3 colour);

protected:
	GLFWwindow* window;

	std::vector<GUIBase*> GUI;

	unsigned int GUIUBO;
};