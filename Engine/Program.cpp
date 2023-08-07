#include "Program.h"
#include "Program.h"
#include "Program.h"
#include "Program.h"
#include "Program.h"
#include "Program.h"
#include "Program.h"

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Program::Program(const std::string* shaderPaths, int* shaderTypes, int shaderCount, inputTypes type)
{
	if (type == filePath)
	{
		initFile(shaderPaths, shaderTypes, shaderCount);
	}
	else
	{
		initCode(shaderPaths, shaderTypes, shaderCount);
	}
	
}

Program::Program(const std::string& vertPath, const std::string& fragPath, inputTypes type)	
{
	std::string shaderPaths[2]{vertPath,fragPath};	//Create arrays for the shader paths and types, then call init function
	int shaderTypes[2]{ GL_VERTEX_SHADER,GL_FRAGMENT_SHADER };
	if (type == filePath)
	{
		initFile(shaderPaths, shaderTypes, 2);
	}
	else
	{
		initCode(shaderPaths, shaderTypes, 2);
	}
}

Program::Program(const std::string& vertPath, const std::string& geomPath, const std::string& fragPath, inputTypes type)
{
	std::string shaderPaths[3]{ vertPath,geomPath,fragPath };	//Create arrays for the shader paths and types, then call init function
	int shaderTypes[3]{ GL_VERTEX_SHADER,GL_GEOMETRY_SHADER,GL_FRAGMENT_SHADER };
	if (type == filePath)
	{
		initFile(shaderPaths, shaderTypes, 3);
	}
	else
	{
		initCode(shaderPaths,shaderTypes, 3);
	}
}

Program::~Program()
{
	for (int i = 0; i < shaderCount; i++)	//Delete all the shaders in the program
	{
		glDetachShader(programID,shaderIDs[i]);
		//glDeleteShader(shaderIDs[i]);
	}
	//delete the program
	glDeleteProgram(programID);

	delete[] shaderIDs;
	shaderIDs = nullptr;
}

void Program::initFile(const std::string* shaderPaths, int* shaderTypes, int shaderCount)
{
	programID = glCreateProgram();	//Create the program
	shaderIDs = new unsigned int[shaderCount];

	for (int i = 0; i < shaderCount; i++)	//Generate the shaders given
	{
		shaderIDs[i] = generateShaderFile(shaderPaths[i], shaderTypes[i]);
	}

	this->shaderCount = shaderCount;

	linkShaders();	//Link the shaders to the program object 
}

void Program::initCode(const std::string* shaderCode, int* shaderTypes, int shaderCount)
{
	programID = glCreateProgram();
	shaderIDs = new unsigned int[shaderCount];
	for (int i = 0; i < shaderCount; i++)
	{
		shaderIDs[i] = generateShaderCode(shaderCode[i], shaderTypes[i]);
	}

	this->shaderCount = shaderCount;

	linkShaders();
}

//Generate and compile a shader object from a file
unsigned int Program::generateShaderFile(const std::string& shaderDir, int shaderType)
{
	unsigned int shaderID;	//Initialise variables for shader and the shader code

	std::string shaderString{};
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);	//Set up errors for if the file isn't read
	try
	{
		shaderFile.open(shaderDir);	//Open the file 

		std::stringstream shaderStream;		//Read the code from the shader
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();	//Close the file

		shaderString = shaderStream.str();//Get the string from the stream
	}
	catch (std::ifstream::failure e)
	{	//Catch errors
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		std::cout << shaderDir << '\n';
		return 0;
	}

	const char* shaderCode = shaderString.c_str();	//Get the shader code as a character array

	return generateShaderCode(shaderCode, shaderType);
}

unsigned int Program::generateShaderCode(const std::string& shaderCode, int shaderType)
{
	unsigned int shaderID = glCreateShader(shaderType);

	const char* cCode = shaderCode.c_str();

	glShaderSource(shaderID, 1, &cCode, NULL);
	glCompileShader(shaderID);

	int success{};

	char infoLog[1024];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;;
		std::cout << shaderCode;
		std::cout << "\n -- --------------------------------------------------- -- " << std::endl;
		return 0;
	}
	return shaderID;
}

bool Program::linkShaders()
{
	for (int i = 0; i < shaderCount; i++)	//Attach all the shaders to the program, then link the program
	{
		glAttachShader(programID, shaderIDs[i]);
	}
	glLinkProgram(programID);

	int success = {};
	char infoLog[1024] = {};
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 1024, NULL, infoLog);
		std::cout << "Error linking shader code: " << '\n' << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		return false;
	}

	for(int i=0;i<shaderCount;i++)
	{
		glDeleteShader(shaderIDs[i]);
	}

	return true;
}

void Program::use()
{
	glUseProgram(programID);
}

void Program::setBool(const char* name, bool value) { glUniform1i(glGetUniformLocation(programID, name), value); }
void Program::setInt(const char* name, int value) { glUniform1i(glGetUniformLocation(programID, name), value); }
void Program::setFloat(const char* name, float value) { glUniform1f(glGetUniformLocation(programID, name), value); }
void Program::setVec2(const char* name, glm::vec2 value) { glUniform2f(glGetUniformLocation(programID, name), value.x, value.y); }
void Program::setVec3(const char* name, glm::vec3 value) { glUniform3f(glGetUniformLocation(programID, name), value.x, value.y, value.z); }
void Program::setVec4(const char* name, glm::vec4 value) { glUniform4f(glGetUniformLocation(programID, name), value.x, value.y, value.z, value.w); }
void Program::setMat4(const char* name, glm::mat4 value) { glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, &value[0][0]); }

void Program::setUniformBufferBlockBinding(const char* bufferName, unsigned int bindingPoint)
{
	glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, bufferName), bindingPoint);
}
