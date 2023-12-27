#include "LevelManager.h"

#include "BaseLevel.h"

LevelManager::LevelManager():currentLevel{-1}
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::addLevel(BaseLevel* level)
{
	levels.push_back(level);
}

void LevelManager::setLevel(int l)//Change level
{
	if (l >= levels.size() || l<0) { return; }	//If l isn't a valid level
	if(currentLevel!=-1){ levels[currentLevel]->closeLevel(); }	//If level was open, close it (only false on initialisation)
	
	currentLevel = l;
	levels[currentLevel]->openLevel();
}

void LevelManager::handleInput(Timer* inputTimer)
{
	levels[currentLevel]->handleInput(inputTimer);
}

void LevelManager::update(Timer* updateTimer)
{
	levels[currentLevel]->update(updateTimer);
}

void LevelManager::render(Timer* renderTimer)
{
	levels[currentLevel]->render(renderTimer);
}

