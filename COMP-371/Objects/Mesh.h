// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Cube.h"
#include "Object.h"

/**
 * \brief Mesh hierarchical structure object
 */
class Mesh : public Object
{
public:
	//Constructors/destructors
	/**
	 * \brief Creates a new empty Mesh object
	 */
	Mesh();
	/**
	 * \brief Mesh destructor, frees up used memory
	 */
	~Mesh();

	//Getters
	/**
	 * \brief Gets the root Cube of this Mesh
	 * \return Pointer to the root Cube object
	 */
	Cube* getRoot() const { return root; }
	/**
	 * \brief Gets the VAO of this Mesh
	 * \return VAO of this Mesh
	 */
	GLuint getVAO() const { return VAO; }

	//Methods
	/**
	* \brief Sets up all necessary objects for rendering
	*/
	void setup() override;
	/**
	* \brief Renders the Mesh
	* \param shader Shader to use for rendering, a lighting shader is used if none is provided
	*/
	void render(Shader* shader = nullptr) const override;
	/**
	 * \brief Resets the Mesh to it's original state
	 */
	void reset();
	/**
	 * \brief Finds cube of the given name within the Mesh
	 * \param name Name of the cube to find
	 * \return	   The cube of the given name, or nullptr if it was not found
	 */
	Cube* findCube(const std::string& name) const;

private:
	//Structs
	/**
	 * \brief Mesh state container
	 */
	struct State
	{
		/// \brief Mesh position
		glm::vec3 position;
		/// \brief Mesh Y rotation
		float yRot;
		/// \brief Mesh Z rotation
		float zRot;
	};

	//Constants
	static const GLfloat vertices[];
	static const GLint indices[];

	//Mesh info
	State start;
	Cube* root;

	//Render values
	glm::vec3 position;
	glm::vec3 size;
	float scaleFactor;
	float yRot;
	float zRot;

	//Friends
	/// \brief Giving friend access to the MeshParser class
	friend class MeshParser;
	///\brief Set input callback function as friend
	friend void key_callback(GLFWwindow*, int, int, int, int);
};
