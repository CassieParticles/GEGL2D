#pragma once
#include <string>


class FileManager
{
public:
	static FileManager& getFileManager();

	void writeToFile(const char* filePath, const std::string& data) { writeToFile(filePath, data.c_str()); }	//Overwrite file with data
	void writeToFile(const char* filePath, const char* data);
	std::string readFromFile(const char* filePath);
protected:
	FileManager();
	~FileManager();
};