// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "../Parsers/FileParser.h"

using std::cout;
using std::endl;
using std::string;
using glm::mat4;
using glm::vec3;

Shader::Shader() : id(0) { }

Shader::Shader(const string vertexPath, const string fragmentPath)
{
	//Read the vertex lightingShader file
	FileParser shaderParser(vertexPath);
	string s = shaderParser.parse();
	const GLchar* source = s.c_str();
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &source, nullptr);
	glCompileShader(vertexShader);

	//Test for lightingShader compilation errors
	const int bufferSize = 512;
	GLint success;
	GLchar info[bufferSize];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, bufferSize, nullptr, info);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\nFile: " << vertexPath << endl << info << endl;
	}

	//Read the fragment lightingShader file
	shaderParser = FileParser(fragmentPath);
	s = shaderParser.parse();
	source = s.c_str();
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &source, nullptr);
	glCompileShader(fragmentShader);
	;
	//Test for lightingShader compilation errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, bufferSize, nullptr, info);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\nFile: " << fragmentPath << endl << info << endl;
	}

	//Create the lightingShader program
	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	//Test for lightingShader program linkin errors
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, bufferSize, nullptr, info);
		cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << info << endl;
	}

	//Free up the memory associated to the shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	if (id != 0)
	{
		glUseProgram(0);
		glDeleteProgram(id);
	}
}

void Shader::use() const
{
	//Use program
	glUseProgram(id);
}

void Shader::setBool(const string& name, const bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setInt(const string& name, const int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const string& name, const float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec3(const string& name, const vec3 value) const
{
	//Set the uniform value
	glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, value_ptr(value));
}

void Shader::setMat4(const string& name, const mat4 value) const
{
	//Set the uniform value
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(value));
}