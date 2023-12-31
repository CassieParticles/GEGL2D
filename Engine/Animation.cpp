#include "Animation.h"

#include <glad/glad.h>
#include <algorithm>

#include "Program.h"

Animation::Animation(const std::string& spriteSheetPath, int frameCount,Program* animationProgram, bool looping):frameCount{frameCount},animationProgram{animationProgram},looping{looping}
{
	spriteSheet = TextureManager::getTexturePtr(spriteSheetPath);

	float frameWidth = 1.f / frameCount;

	for (int i = 0; i < frameCount; i++)
	{
		float left = frameWidth * i;
		float right = frameWidth * (i + 1);

		frame f;
		f.tl = { left,0 };
		f.bl = { left,1 };
		f.tr = { right,0 };
		f.br = { right,1 };

		frames.push_back(f);
	}

	frameSize = { frameWidth * spriteSheet.width,spriteSheet.height };
}

Animation::Animation(texture spriteSheet, int frameCount, Program* animationProgram, bool looping):spriteSheet{ spriteSheet }, frameCount{ frameCount }, animationProgram{ animationProgram }, looping{ looping }
{
	float frameWidth = 1.f / frameCount;
	for(int i=0;i<frameCount;i++)
	{
		float left = frameWidth * i;
		float right = frameWidth * (i + 1);

		frame f;
		f.tl = { left,0 };
		f.bl = { left,1 };
		f.tr = { right,0 };
		f.br = { right,1 };

		frames.push_back(f);
	}
}

Animation::~Animation()
{
}

void Animation::update(float deltaTime)
{
	sumTime += deltaTime;
	while (sumTime > frameTime * frameCount && looping)
	{
		sumTime -= frameTime * frameCount;
	}
	ended = sumTime > frameTime * frameCount && !looping;
}

void Animation::reset()
{
	sumTime = 0;
	ended = false;
}

void Animation::setCurrentFrame()
{
	int cFrame = sumTime / frameTime;	//Get the index of which frame
	frame f = frames.at(std::min(cFrame,static_cast<int>(frames.size()-1)));
	
	animationProgram->setVec2("texCoords[0]", f.tl);		//Uniform should always be called "texCoords" in shaders
	animationProgram->setVec2("texCoords[1]", f.tr);
	animationProgram->setVec2("texCoords[2]", f.bl);
	animationProgram->setVec2("texCoords[3]", f.br);

	animationProgram->setInt("animationFlipped", flipped);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, spriteSheet.textureID);
	



	animationProgram->setInt("spriteSheet", 0);
}
