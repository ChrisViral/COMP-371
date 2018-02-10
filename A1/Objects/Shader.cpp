// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 1
// Feburary 8th 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::stringstream;
using glm::mat4;
using glm::vec3;

Shader::Shader() : id(0) { }

Shader::Shader(const string vertexPath, const string fragmentPath)
{
	//Read the vertex shader file
	string s = readFile(vertexPath);
	const GLchar* source = s.c_str();
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &source, nullptr);
	glCompileShader(vertexShader);

	//Test for shader compilation errors
	const int bufferSize = 512;
	GLint success;
	GLchar info[bufferSize];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, bufferSize, nullptr, info);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << endl;
	}

	//Read the fragment shader file
	s = readFile(fragmentPath);
	source = s.c_str();
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &source, nullptr);
	glCompileShader(fragmentShader);
	;
	//Test for shader compilation errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, bufferSize, nullptr, info);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info << endl;
	}

	//Create the shader program
	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	//Test for shader program linkin errors
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

Shader::~Shader() { }

void Shader::use() const
{
	//Use program
	glUseProgram(id);
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

string Shader::readFile(const string file)
{
	ifstream f;
	//Set exception bits
	f.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		//Open file
		f.open(file);

		//Read to string buffer
		stringstream ss;
		ss << f.rdbuf();

		//Convert to string
		string s = ss.str();
		return s;
	}
	catch (ifstream::failure e)
	{
		//If error happens, print out error then return empty string
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << e.what() << endl;
		return "";
	}
}
