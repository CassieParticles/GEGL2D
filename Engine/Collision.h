#pragma once
#include <glm.hpp>

struct line
{
	glm::vec2 A;
	glm::vec2 B;
};

struct rect
{
	glm::vec2 blCorner;
	glm::vec2 size;

	float angle;	//Radians
};


//Collisions return a boolean of if a collision occured, pointers used to return any other needed info
namespace Collision
{
	bool checkLineLine(line* lineA, line* lineB, glm::vec2* collidingPoint);	
	bool checkLineRect(rect* r, line* l, line* collidingLine);

	bool checkRectRect(rect* r1, rect* r2);

	bool checkPointRect(rect* r, glm::vec2* point);
}