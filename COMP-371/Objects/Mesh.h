// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Animation.h"
#include "Collider.h"
#include "Cube.h"
#include "Object.h"

#define POINTS 8

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
	 * \brief Copy constructor, creates a copy of the given Mesh
	 * \param mesh Mesh to copy
	 */
	Mesh(const Mesh& mesh);
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
	/**
	 * \brief Gets the collider associated to this model
	 * \return 
	 */
	Collider* getCollider() const { return collider; }

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
	/**
	 * \brief Calculates the model matrix for the base mesh
	 * \return The mesh's model matrix
	 */
	glm::mat4 calculateModelMatrix() const;
	void randomize();

	//Vertices for collider calculation
	static const glm::vec4 points[];

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
	Collider* collider;
	Animation* animation;

	//Render values
	glm::vec3 position;
	glm::vec3 size;
	float scaleFactor;
	float yRot;
	float zRot;

	//Friends
	friend class Animation;
	friend class Collider;
	friend class MeshParser;
	friend void key_callback(GLFWwindow*, int, int, int, int);
};