#include "Font.h"

#include <glad/glad.h>

Font::Font(std::string characterSet, character* characterData)
{
	for(int i=0;i< characterSet.size();i++)	//Add the characters to the map
	{
		characters.insert({ characterSet.at(i),characterData[i]});
	}
}

Font::~Font()
{
	for(auto&& [f,s]:characters)
	{
		glDeleteTextures(1, &s.textureID);
	}
}


