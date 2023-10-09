#include "GameObjects.h"

#include<GLAD/glad.h>
#include <glm.hpp>

namespace GameObjects
{
	void genTextureSquare(unsigned int* vao, unsigned int* posVbo, unsigned int* indexEbo)
	{
		constexpr float vertexPos[8]	//Constants to be put into the buffers
		{
			0,0,
			1,0,
			1,1,
			0,1
		};

		constexpr int indices[6]
		{
			0,2,1,
			0,3,2
		};

		glGenVertexArrays(1, vao);	//Create the VAO
		glBindVertexArray(*vao);

		glGenBuffers(1, posVbo);
		glBindBuffer(GL_ARRAY_BUFFER, *posVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, indexEbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexEbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
}