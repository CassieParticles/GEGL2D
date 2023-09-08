#include "Collision.h"

#include "MathsFunctions.h"

#include <vector>
#include <algorithm>
#include <iostream>

namespace Collision
{
	bool checkLineLine(line* lineA, line* lineB, glm::vec2* collidingPoint)
	{
		glm::vec2 dA = lineA->B - lineA->A;	//Get the vector from point A to B on each line
		glm::vec2 dB = lineB->B - lineB->A;

		float denom = dB.y * dA.x - dB.x * dA.y;
		if (denom == 0)	//If denom is 0, then the lines are parallel
		{
			return false;
		}

		float invDenom = 1.f / denom;

		float t1 = (dB.x * (lineA->A.y - lineB->A.y) - dB.y * (lineA->A.x - lineB->A.x)) * invDenom;
		float t2 = (dA.x * (lineA->A.y - lineB->A.y) - dA.y * (lineA->A.x - lineB->A.x)) * invDenom;

		bool collide = t1 >= 0 && t1 <= 1 && t2>=0 && t2 <= 1;

		if (collidingPoint != nullptr && collide)
		{
			*collidingPoint = lineA->A + dA * t1;
		}

		return collide;
	}

	bool checkLineRect(rect* r, line* l, line* collidingLine)
	{
		float cosAngle = cos(r->angle);	//Get cosine and sin of rotated angle
		float sinAngle = sin(r->angle);
		glm::mat2x2 rotMatrix{cosAngle, -sinAngle, sinAngle, cosAngle};	//Rotate the corners

		glm::vec2 tl = r->blCorner;
		glm::vec2 tr = r->blCorner + rotMatrix * glm::vec2{r->size.x, 0};
		glm::vec2 bl = r->blCorner + rotMatrix * glm::vec2{0, r->size.y};
		glm::vec2 br = r->blCorner + rotMatrix * r->size;
		
		line edges[4] = {  
			{tl,tr},
			{tr,br},
			{br,bl},
			{bl,tl}
		};

		bool collide{};

		bool gotFirstCollisionPoint{};	
		bool gotSecondCollisionPoint{};

		if (checkPointRect(r, &l->A))	//Check to see if either end of the line is in the rect
		{
			gotFirstCollisionPoint = true;
			collide = true;
			if (collidingLine != nullptr) { collidingLine->A = l->A; }
		}

		if (checkPointRect(r, &l->B))
		{
			gotSecondCollisionPoint = true;
			collide = true;
			if (collidingLine != nullptr) { collidingLine->B = l->B; }
		}

		for (int i = 0; i < 4; i++)	//Collision is checked by creating 4 lines to represent the sides of the rect, and checking each of these
		{
			glm::vec2* point{nullptr};		
			if (collidingLine == nullptr)
			{
				point = nullptr;
			}
			else if (!gotFirstCollisionPoint)	//If the first point isn't gotten yet
			{
				point = &collidingLine->A;
			}
			else if (!gotSecondCollisionPoint)	//If the first point is gotten, but the second one isn't
			{
				point = &collidingLine->B;
			}
			else								//If both points are gotten
			{
				break;
			}

			bool currentLineCollide = checkLineLine(edges + i, l, point);

			//Boolean logic to if the first and second vertices are gotten
			gotSecondCollisionPoint = currentLineCollide && gotFirstCollisionPoint || gotSecondCollisionPoint;
			gotFirstCollisionPoint = currentLineCollide || gotFirstCollisionPoint;
			

			collide = collide || currentLineCollide;
		}

		if(collidingLine==nullptr)
		{
			return collide;
		}

		if (MathsFunctions::getDistSqr(collidingLine->A, l->A) > MathsFunctions::getDistSqr(collidingLine->B, l->A))
		{
			//Line is wrong way round, swap it
			glm::vec2 temp = collidingLine->A;
			collidingLine->A = collidingLine->B;
			collidingLine->B = temp;
		}

		return collide;
	}

	bool checkRectRect(rect* r1, rect* r2)
	{
		if(r1->angle==0&&r2->angle==0)		//AABB vs AABB collision, much simpler collision detection method can be used
		{
			float minX = r1->blCorner.x;
			float maxX = r1->blCorner.x+r1->size.x;

			float minY = r1->blCorner.y;
			float maxY = r1->blCorner.y + r1->size.y;

			if(r2->blCorner.x<minX&&r2->blCorner.x+r2->size.x<minX)	//Rectangle is too far left
			{
				return false;
			}
			if(r2->blCorner.x>maxX&&r2->blCorner.x+r2->size.x>maxX)	//Rectangle is too far right
			{
				return false;
			}
			if(r2->blCorner.y<minY&&r2->blCorner.y+r2->size.y<minY)	//Rectangle is too far down
			{
				return false;
			}
			if(r2->blCorner.y>maxY&&r2->blCorner.y+r2->size.y>maxY)	//Rectangle is too far up
			{
				return false;
			}
			return true;
		}
		//OBB vs OBB collision, shenanigans abound

		const float cosAngleA = cos(r1->angle);	//Get cosine and sin of rotated angleA
		const float sinAngleA = sin(r1->angle);

		glm::mat2x2 rotMatrixA{cosAngleA, -sinAngleA, sinAngleA, cosAngleA};	//Rotation matrix

		glm::vec2 rectACorners[4]	//bl, br, tl, tr (rotated)
		{
			r1->blCorner + rotMatrixA*(glm::vec2{0,0}*r1->size),
			r1->blCorner + rotMatrixA*(glm::vec2{1,0}*r1->size),
			r1->blCorner + rotMatrixA*(glm::vec2{0,1}*r1->size),
			r1->blCorner + rotMatrixA*(glm::vec2{1,1}*r1->size),
		};

		const float cosAngleB = cos(r2->angle);//Get sin and cosine of rotated angle B
		const float sinAngleB = sin(r2->angle);

		glm::mat2x2 rotMatrixB{cosAngleB, -sinAngleB, sinAngleB, cosAngleB};

		glm::vec2 rectBCorners[4]	//bl, br, tl, tr (rotated)
		{
			r2->blCorner + rotMatrixB * (glm::vec2{0,0}*r2->size),
			r2->blCorner + rotMatrixB * (glm::vec2{1,0}*r2->size),
			r2->blCorner + rotMatrixB * (glm::vec2{0,1}*r2->size),
			r2->blCorner + rotMatrixB * (glm::vec2{1,1}*r2->size),
		};

		//Makes use of SAT (separating axis theorem) to test if the 2 OBBs are intersecting, if it can find a line between the 2 rects, they are not intersecting
		glm::vec2 lineChecks[4]	//local x,y of rect A, then local x,y of rect B
		{
			rectACorners[1] - rectACorners[0],
			rectACorners[2] - rectACorners[0],
			rectBCorners[1] - rectBCorners[0],
			rectBCorners[2] - rectBCorners[0]
		};

		for(int i=0;i<4;i++)	//Iterate through each line
		{
			float minA{  999999999999999.f };	//Make the minimum and maximum arbitrarily high and low so they are overwritten immediately
			float maxA{ -999999999999999.f };
			for(int A=0;A<4;A++)	//Get the largest and smallest projections
			{
				float proj=MathsFunctions::projectPointLineSclr(lineChecks[i], rectACorners[A]);
				minA = std::min(minA, proj);
				maxA = std::max(maxA, proj);
			}

			float minB{ 999999999999999.f };	//Make the minimum and maximum arbitrarily high and low so they are overwritten
			float maxB{ -999999999999999.f };
			for(int B=0;B<4;B++)
			{
				float proj = MathsFunctions::projectPointLineSclr(lineChecks[i], rectBCorners[B]);
				minB = std::min(minB, proj);
				maxB = std::max(maxB, proj);
			}
			//3 cases:
			//minB and maxB are both smaller then minA/both larger then maxA (not intersecting) (checking for this one)
			//minB is smaller then minA and maxB is larger then maxA (intersecting)
			//minB/maxB is between minA & maxB (intersecting)
			if(minB<minA&&maxB<minA || minB>maxA&&maxB>maxA)	//If both B points are same side of A, separated on the axis, according to SAT, they are not intersecting
			{
				return false;
			}
		}
		return true;	//Must be intersecting on at least one line
	}


	bool checkPointRect(rect* r, glm::vec2* point)
	{
		float cosAngle = cos(r->angle);	//Get cosine and sin of rotated angle
		float sinAngle = sin(r->angle);
		glm::mat2x2 rotMatrix{cosAngle, -sinAngle, sinAngle, cosAngle};	//Rotate the corners
		glm::mat2x2 invRotMatrix = glm::inverse(rotMatrix);

		glm::vec2 translatedPoint = *point - r->blCorner;
		glm::vec2 rotatedPoint = invRotMatrix * translatedPoint;
		
		return rotatedPoint.x > 0 && rotatedPoint.x < r->size.x && rotatedPoint.y > 0 && rotatedPoint.y < r->size.y;
	}


	
}