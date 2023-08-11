#include "GUIText.h"

#include "Font.h"
#include "Engine/Program.h"
#include "glad/glad.h"

GUIText::GUIText(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size,GLFWwindow* window, std::string textString, Font* fontUsed,glm::vec3 colour, int characterLimit, int pixelLimit):GUIBase(position,relativeTo,size,window),font{fontUsed},colour{colour},characterLimit{characterLimit},pixelLimit{pixelLimit}
{
	renderProgram = new Program("Engine/Shaders/GUIText.vert", "Engine/Shaders/GUIText.frag",Program::filePath);
	renderProgram->setUniformBufferBlockBinding("windowData", 0);

	generateNewString(textString);
}

GUIText::~GUIText()
{
	delete[] characterArray;
}

void GUIText::generateNewString(std::string newString)
{
	//If the strings are identical, don't do anything
	if (newString == textString) { return; }

	//Cleanup old array (textures don't need to be deleted, since that is handled in the font)
	if(characterArray!=nullptr){ delete[] characterArray; }
	

	characterArray = new character[newString.size()];

	int characterCount = 0;
	int pixelCount = 0;

	for(int i=0;i< newString.size();i++)
	{
		character c= font->getCharacter(newString.at(i));	//Get the next character

		if (characterLimit != -1 && characterCount + 1 >= characterLimit) { break; }	//Check if adding the new character would exceed either limit
		if (pixelLimit != -1 && pixelCount + (c.advance >> 6) * size.x >= pixelLimit) { break; }

		characterArray[i] = c;
		characterCount++;
		pixelCount += (characterArray[i].advance >> 6) * size.x;

	}

	if(characterCount<newString.size())
	{
		textString = newString.substr(0, characterCount);
	}else
	{
		textString = newString;
	}
}

void GUIText::render()
{
	/*
	 Bind the buffers and array
		VAO + element array
	Use program
		Set uniforms
			yOffset(y position of text)
			textureID(0)
			
			relativeTo
			textColour
	 Store curXOffset(start 0)
	 Iterate through each character
		Set xOffset to curXOffset
		Set size to the size of the character
		Bind character texture
		Render character to screen
		Add characterWidth to curXOffset
	 */

	if (!draw) { return; }

	glBindVertexArray(vaoId);	//Bind VAO and element array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

	renderProgram->use();	//use program and set non-character specific uniforms
	renderProgram->setVec2("relativeTo", relativeTo);
	renderProgram->setVec2("scale", size);

	renderProgram->setVec3("colour", colour);	
	renderProgram->setInt("tex", 0);


	float curXPos = position.x;
	for(int i=0;i<textString.length();i++)
	{
		const character& current = characterArray[i];
		renderProgram->setFloat("xPos", curXPos+current.bearing.x*size.x);
		renderProgram->setFloat("yPos", position.y-(current.size.y-current.bearing.y)*size.y);
		renderProgram->setVec2("size", current.size);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, current.textureID);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		curXPos += (current.advance >> 6) * size.x;	//Bit shifted to get in pixels 
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

