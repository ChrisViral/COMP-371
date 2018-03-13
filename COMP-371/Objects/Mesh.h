#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Cube.h"

/**
 * \brief Mesh hierarchical structure object
 */
class Mesh
{
public:
	/**
	 * \brief Creates a new empty Mesh object
	 */
	Mesh();
	/**
	 * \brief Mesh destructor, frees up used memory
	 */
	~Mesh();

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
	 * \brief Sets up the various OpenGL container objects
	 */
	void setup();
	/**
	 * \brief Calculates the joint axis for all children cubes
	 * \return The current joint axis
	 */
	glm::vec3 getJointAxis() const;
	/**
	 * \brief Calculates the current model matrix for this Mesh object
	 * \return Model matrix for the whole Mesh
	 */
	void renderMesh() const;
	/**
	 * \brief Resets the Mesh to it's original state
	 */
	void reset();

private:
	/**
	 * \brief Mesh state container
	 */
	struct State
	{
		/// \brief Mesh position
		glm::vec3 position;
		/// \brief Mesh size
		float size;
		/// \brief Mesh Y rotation
		float yRot;
		/// \brief Mesh Z rotation
		float zRot;
	};

	/// \brief Y rotation axis
	static const glm::vec3 yAxis;
	/// \brief Z rotation axis
	static const glm::vec3 zAxis;
	/// \brief Cube vertices
	static const GLfloat vertices[];
	/// \brief Cube face indices
	static const GLint indices[];

	/// \brief Mesh original state
	State start;

	/// \brief GL container objects
	GLuint VAO, VBO, EBO;
	/// \brief Setup flag
	bool set;
	/// \brief Root cube of the Mesh
	Cube* root;
	/// \brief World position of the Mesh
	glm::vec3 position;
	/// \brief Scale size of the Mesh
	float size;
	/// \brief Y rotation of the Mesh, in degrees
	float yRot;
	/// \brief Z rotation of the Mesh, in degrees
	float zRot;

	/// \brief Giving friend access to the MeshParser class
	friend class MeshParser;
	///\brief Set input callback function as friend
	friend void key_callback(GLFWwindow*, int, int, int, int);
};
