#pragma once
#include <glm.hpp>

namespace MathsFunctions
{
	inline float normalise(float a, float b, float f){ return (f - a) / (b - a); }

	inline glm::vec2 getMidPtX(glm::vec2 A, glm::vec2 B, float a, float b){ return glm::vec2(A.x + normalise(a, b, 0) * (B.x - A.x), A.y); }
	inline glm::vec2 getMidPtY(glm::vec2 A, glm::vec2 B, float a, float b){ return glm::vec2(A.x, A.y + normalise(a, b, 0) * (B.y - A.y)); }

	inline float getDistSqr(glm::vec2 A, glm::vec2 B){ return (B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y); }

	inline glm::vec2 projectPointLine(glm::vec2 line, glm::vec2 point) { return line * glm::dot(line, point) / glm::dot(line, line); }
	inline float projectPointLineSclr(glm::vec2 line, glm::vec2 point) { return glm::dot(line, point) / glm::dot(line, line); }
};