#pragma once

#include <glm.hpp>
#include <map>

class GUIText;

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

	character getCharacter(char c) { return characters[c]; }

protected:
	std::map<char, character> characters;
};