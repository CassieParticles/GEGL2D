#include "GUIManager.h"

#include <glad/glad.h>
#include <glfw3.h>

#include "GUIColourRect.h"
#include "GUITextureRect.h"
#include "../Program.h"
#include "Engine/TextureManager.h"

GUIManager::GUIManager(GLFWwindow* window):window{window}
{
	int x, y;	//Get the window size
	glfwGetWindowSize(window, &x, &y);
	windowSize={x, y };

	glGenBuffers(1, &GUIUBO);		//Initialise the uniform buffer
	glBindBuffer(GL_UNIFORM_BUFFER, GUIUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::ivec2), &windowSize, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, GUIUBO);

	glGenFramebuffers(1, &frameBuffer);	//Generate the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glGenTextures(1, &frameTexture);	//Generate texture for frame buffer
	glBindTexture(GL_TEXTURE_2D, frameTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Bind texture to frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexture, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenVertexArrays(1, &vertexArray);	//Generate vertex array to draw GUI texture to screen
	glGenBuffers(2, buffers);
	glBindVertexArray(vertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);	//Set up vertex position buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);	//Set up indices buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	textureProgram = new Program{ "Engine/Shaders/textureRender.vert","Engine/Shaders/textureRender.frag" ,Program::filePath};
}

GUIManager::~GUIManager()
{
	for (int i = 0; i < GUI.size(); i++)
	{
		delete GUI.at(i);
	}
	glDeleteFramebuffers(1, &frameBuffer);
}

void GUIManager::render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);	//Bind frame buffer

	glClearColor(0, 0, 0, 0);	//Clear the frame buffer
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, 1024, 1024);

	for(int i=0;i<GUI.size();i++)	//Draw all GUI elements
	{
		GUI.at(i)->render();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);	//Unbind the frame buffer
	glViewport(0, 0, windowSize.x, windowSize.y);

	textureProgram->use();

	textureProgram->setInt("tex", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, frameTexture);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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
