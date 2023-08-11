#include "GUIText.h"

#include "Font.h"
#include "Engine/Program.h"
#include "glad/glad.h"

GUIText::GUIText(glm::vec2 position, glm::vec2 relativeTo, glm::vec2 size,GLFWwindow* window, std::string textString, Font* fontUsed,glm::vec3 colour):GUIBase(position,relativeTo,size,window),font{fontUsed},colour{colour}
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

	for(int i=0;i< newString.size();i++)
	{
		characterArray[i] = font->getCharacter(newString.at(i));
	}
	textString = newString;
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

