// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 1
// Feburary 8th 2018

#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>

/**
 * \brief Shader Program wrapper object handling a Vertex and a Fragment shader
 */
class Shader
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new empty shader, with no associated programs
	 */
	Shader();
	/**
	 * \brief Creates a new Shader from the given vertex shader and fragment shader file pathes
	 * \param vertexPath   Path (local or absolute) to the vertex shader file
	 * \param fragmentPath Path (local or absolute) to the fragment shader file
	 */
	Shader(const std::string vertexPath, const std::string fragmentPath);
	/**
	 * \brief Frees up the memory associated to this shader
	 */
	~Shader();

	//Setters/Getters
	/**
	 * \brief Gets the shader program ID associated to this Shader object
	 * \return The program ID
	 */
	GLuint getID() const { return id; }

	//Methods
	/**
	 * \brief Sets OpenGL to use this Shader Program
	 */
	void use() const;
	/**
	* \brief Sets a uniform Vector3 value of the given name
	* \param name  Name of the uniform value
	* \param value Vector3 value to set
	*/
	void setVec3(const std::string& name, const glm::vec3 value) const;
	/**
	* \brief Sets a uniform Matrix4 value of the given name
	* \param name  Name of the uniform value
	* \param value Matrix4 value to set
	*/
	void setMat4(const std::string& name, const glm::mat4 value) const;

private:
	//Shader program ID
	GLuint id;

	//Static methods
	/**
	 * \brief Reads all the contents of a text file and returns it in one string
	 * \param file Path (local or absolute) of the file to read
	 * \return The text contained in the file
	 */
	static std::string readFile(std::string file);
};

