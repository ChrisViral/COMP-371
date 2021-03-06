// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
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
	 * \brief Copy constructor, creates a copy of the given cube
	 * \param cube Cube to copy
	 */
	Cube(const Cube& cube, Mesh* mesh);
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
	/**
	 * \brief Gets the model matrix for this cube, unscaled
	 * \param model Model matrix of the parent
	 * \return      The resulting model matrix
	 */
	glm::mat4 calculateModelMatrix(glm::mat4 model) const;
	/**
	 * \brief Adds all the vertices from the cube in world coordinates to the vector
	 * \param model  Model matrix of the parent
	 * \param points Vector to add the coordinates to
	 */
	void fillPoints(glm::mat4 model, std::vector<glm::vec3>& points);

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
	friend class MeshParser;
	friend void key_callback(GLFWwindow*, int, int, int, int);
};
