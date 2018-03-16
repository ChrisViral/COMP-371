// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

//Forward declarations
class Mesh;
class Shader;

/**
 * \brief Cube element of a mesh
 */
class Cube
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new Cube with the parent Mesh
	 * \param mesh Pointer to the parent mesh
	 */
	explicit Cube(Mesh* mesh);
	/**
	 * \brief Destructor, frees up used memory
	 */
	~Cube();

	//Getters
	/**
	 * \brief Determines if this Cube is the root of the Mesh
	 * \return True if this is the root, false otherwise
	 */
	bool isRoot() const { return parent == nullptr; }
	/**
	 * \brief Gets the name of this Cube
	 * \return Name of the Cube
	 */
	std::string getName() const { return name; }
	/**
	 * \brief Gets the parent Cube of this instance
	 * \return A pointer to the parent, can be null if the Cube is the root
	 */
	Cube* getParent() const { return parent; }
	/**
	 * \brief Gets the children of this Cube
	 * \return Vector containing pointers to all children
	 */
	std::vector<Cube*> getChildren() const { return children; }

	//Methods
	/**
	 * \brief Renders the Cube
	 * \param model  Model matrix of the parent or mesh
	 * \param shader Shader to use to render
	 */
	void render(glm::mat4 model, Shader* shader) const;

private:
	//Info fields on the cube
	std::string name;
	glm::vec3 colour;
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3 offset;
	float angle, startAngle;

	//Parents and children
	Mesh* mesh;
	Cube* parent;
	std::vector<Cube*> children;

	//Friends
	/// \brief Set MeshParser as friend
	friend class MeshParser;
	///\brief Set input callback function as friend
	friend void key_callback(GLFWwindow*, int, int, int, int);
};
