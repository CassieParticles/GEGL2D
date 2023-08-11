#pragma once

#include <glm.hpp>
#include <map>
#include <string>

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
	Font(std::string characterSet, character* characterData, int height);
	~Font();

	character getCharacter(char c) { return characters[c]; }

	int getHeight() { return height; }

protected:
	std::map<char, character> characters;

	int height;
};