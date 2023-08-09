#pragma once

#include <glm.hpp>
#include <map>


struct character
{
	unsigned int textureID;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class Font
{
public:
	Font(char* chrs, character* characterData, int characterCount);
	~Font();

protected:
	std::map<char, character> characters;
};