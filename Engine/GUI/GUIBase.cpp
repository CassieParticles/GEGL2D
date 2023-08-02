#include "GUIBase.h"

#include <glad/glad.h>
#include <glfw3.h>

GUIBase::GUIBase(glm::vec2 position, glm::vec2 size, GLFWWindow* window):position{position},size{size},window{window}
{

}

GUIBase::~GUIBase()
{
	delete renderProgram;

	glDeleteBuffers(1, vboIds);
	glDeleteVertexArrays(1, &vaoId);
}
