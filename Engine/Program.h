#pragma once
#include <string>
#include <glm.hpp>


class Program
{
public:

	enum inputTypes
	{
		filePath,
		sourceCodes
	};

	//General case for 
	Program(const std::string* shaderPaths, int* shaderTypes, int shaderCount, inputTypes type);	


	//Common cases, uses first constructor, but makes writing easier
	Program(const std::string& vertPath, const std::string& fragPath, inputTypes type);	
	Program(const std::string& vertPath, const std::string& geomPath, const std::string& fragPath, inputTypes type);

	~Program();

	void use();

	void setBool(const char* name, bool value);	//Set uniforms within shaders
	void setInt(const char* name, int value);
	void setFloat(const char* name, float value);
	void setVec2(const char* name, glm::vec2 value);
	void setVec3(const char* name, glm::vec3 value);
	void setVec4(const char* name, glm::vec4 value);
	void setMat4(const char* name, glm::mat4 value);

	unsigned int getProgramID() { return programID; }
private:
	unsigned int programID;	//ID of this specific program

	unsigned int* shaderIDs;//IDs of all shaders within the program, as well as the number of shaders
	int shaderCount;

	void initFile(const std::string* shaderPaths, int* shaderTypes, int shaderCount);	//Set up the program (cannot call one function from another function)

	void initCode(const std::string* shaderCode, int* shaderTypes, int shaderCount);	//Set up program using shader code directly

	//Compile a shader at the given file location and return the ID of the generated shader
	unsigned int generateShaderFile(const std::string& shaderDir, int shaderType);	
	unsigned int generateShaderCode(const std::string& shaderCode, int shaderType);

	//Link all shaders together into the program, returns if shaders were linked successfully
	bool linkShaders();
};