#include "FileManager.h"
#include <fstream>
#include <iostream>

FileManager::FileManager()
{
	
}

FileManager::~FileManager()
{
}

FileManager& FileManager::getFileManager()
{
	static FileManager manager{};
	return manager;
}


void FileManager::writeToFile(const char* filePath, const char* data)
{
	std::ofstream file{filePath};
	if (!file.is_open()) { return; }	//File failed to open

	file << data;

	file.close();
}

std::string FileManager::readFromFile(const char* filePath)
{
	std::string data;
	std::ifstream file{filePath};
	if (!file.is_open()) { return ""; }

	while (!file.eof())
	{
		char c;
		file >> std::noskipws >> c;
		data += c;
	}
	return data;
}
