#include "GUIManager.h"

#include "GUIColourRect.h"
#include "GUITextureRect.h"

GUIManager::GUIManager(GLFWwindow* window):window{window}
{

}

GUIManager::~GUIManager()
{
	for (int i = 0; i < GUI.size(); i++)
	{
		delete GUI.at(i);
	}
}

void GUIManager::render()
{
	for(int i=0;i<GUI.size();i++)
	{
		GUI.at(i)->render();
	}
}

GUIColourRect* GUIManager::createColourRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, glm::vec3 colour)
{
	GUIColourRect* gui = new GUIColourRect{ position,relativeTo,size,window,colour };
	GUI.push_back(gui);

	return gui;
}

GUITextureRect* GUIManager::createTextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, const std::string& textureDir, glm::vec3 colour)
{
	GUITextureRect* gui = new GUITextureRect{ position,relativeTo,size,window,textureDir,colour };
	GUI.push_back(gui);

	return gui;
}

GUITextureRect* GUIManager::createTextureRect(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, unsigned int textureID, glm::vec3 colour)
{
	GUITextureRect* gui = new GUITextureRect{ position,relativeTo,size,window,textureID,colour };
	GUI.push_back(gui);

	return gui;
}
