#include "Font.h"

#include <glad/glad.h>

Font::Font(char* chrs, character* characterData, int characterCount)
{
	for(int i=0;i<characterCount;i++)	//Add the characters to the map
	{
		characters.insert({ chrs[i],characterData[i] });
	}
}

Font::~Font()
{
	for(auto&& [f,s]:characters)
	{
		glDeleteTextures(1, &s.textureID);
	}
}


