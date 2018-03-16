// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>

/**
 * \brief Shader Program wrapper object handling a Vertex and a Fragment lightingShader
 */
class Shader
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new empty Shader, with no associated programs
	 */
	Shader();
	/**
	 * \brief Creates a new Shader from the given vertex Shader and fragment Shader file pathes
	 * \param vertexPath   Path (local or absolute) to the vertex Shader file
	 * \param fragmentPath Path (local or absolute) to the fragment Shader file
	 */
	Shader(const std::string vertexPath, const std::string fragmentPath);
	/**
	* \brief Creates a new Shader from the given vertex Shader, geometry Shader, and fragment Shader file pathes
	* \param vertexPath   Path (local or absolute) to the vertex Shader file
	* \param geometryPath Path (local or absolute) to the geometry Shader file
	* \param fragmentPath Path (local or absolute) to the fragment Shader file
	*/
	Shader(const std::string vertexPath, const std::string geometryPath, const std::string fragmentPath);
	/**
	 * \brief Frees up the memory associated to this lightingShader
	 */
	~Shader();

	//Setters/Getters
	/**
	 * \brief Gets the lightingShader program ID associated to this Shader object
	 * \return The program ID
	 */
	GLuint getID() const { return id; }

	//Methods
	/**
	 * \brief Sets OpenGL to use this Shader Program
	 */
	void use() const;
	/**
	* \brief Sets a uniform bool value of the given name
	* \param name  Name of the uniform value
	* \param value Bool value to set
	*/
	void setBool(const std::string& name, const bool value) const;
	/**
	* \brief Sets a uniform integer value of the given name
	* \param name  Name of the uniform value
	* \param value Integer value to set
	*/
	void setInt(const std::string& name, const int value) const;
	/**
	* \brief Sets a uniform float value of the given name
	* \param name  Name of the uniform value
	* \param value Float value to set
	*/
	void setFloat(const std::string& name, const float value) const;
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
};

