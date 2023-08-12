#include "GUIManager.h"

#include <glad/glad.h>
#include <glfw3.h>
#include <memory>
#include <iostream>


#include <ft2build.h>
#include FT_FREETYPE_H

#include <Engine/GUI.h>

#include "../Program.h"
#include "Engine/TextureManager.h"

GUIManager::GUIManager(GLFWwindow* window,Input* input):window{window},input{input}
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
	for(int i=0;i<fonts.size();i++)
	{
		delete fonts.at(i);
	}

	glDeleteFramebuffers(1, &frameBuffer);
}

void GUIManager::update()
{
	for(int i=0;i<GUI.size();i++)
	{
		GUI.at(i)->update();
	}
}

void GUIManager::render()
{

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

GUIButton* GUIManager::createButton(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, glm::vec3 colour, std::function<void()> func)
{
	GUIButton* gui = new GUIButton{ position,relativeTo,size,window,colour,input,func };
	GUI.push_back(gui);

	return gui;
}

GUIText* GUIManager::createText(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, std::string textString, Font* fontUsed, glm::vec3 colour, int characterLimit, int pixelLimit)
{
	GUIText* gui = new GUIText{ position,relativeTo,size,window,textString,fontUsed,colour,characterLimit,pixelLimit };
	GUI.push_back(gui);

	return gui;
}

GUIToggleButton* GUIManager::createToggleButton(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, std::string inactiveFilePath, std::string activeFilePath)
{
	GUIToggleButton* gui = new GUIToggleButton(position, relativeTo, size, window, input, inactiveFilePath, activeFilePath);
	GUI.push_back(gui);

	return gui;
}

GUITextBox* GUIManager::createTextBox(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size, Font* font, glm::vec3 dColour, glm::vec3 sColour, std::string acceptedCharacters)
{
	GUITextBox* gui = new GUITextBox(position, relativeTo, size, window, input, font, dColour, sColour, acceptedCharacters);
	GUI.push_back(gui);

	return gui;
}


Font* GUIManager::createFont(const char* filePath, int height,std::string characterSet)
{
	//Create and initialise the library
	FT_Library ft;
	if(FT_Init_FreeType(&ft))
	{
		std::cout << "Error in initializing library\n";
		return nullptr;
	}
	//Create and initialise the face
	FT_Face face;
	if(FT_New_Face(ft,filePath,0,&face))
	{
		std::cout << "Error in creating face\n";
		return nullptr;
	}

	FT_Set_Pixel_Sizes(face, 0, height);	//0 width means it calculates appropriate width from height

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	char* charArray = new char[characterSet.size()];
	character* charDataArray = new character[characterSet.size()];

	for(int i=0;i<characterSet.size();i++)
	{
		if(FT_Load_Char(face,characterSet.at(i), FT_LOAD_RENDER))
		{
			std::cout << "Error in loading character " << characterSet[i] << '\n';
			continue;
		}
		//Generate the texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		character chr = { texture,glm::ivec2{face->glyph->bitmap.width, face->glyph->bitmap.rows},	//Store character data
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x };

		charArray[i] = characterSet.at(i);
		charDataArray[i] = chr;
	}

	Font* f = new Font{ charArray,charDataArray,height };

	delete[] charArray;	//Free up arrays and freefont stuff
	delete[] charDataArray;
	 
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	return f;
}

