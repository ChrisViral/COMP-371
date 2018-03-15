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
	void setup() override;
	/**
	 * \brief Calculates the current model matrix for this Mesh object
	 * \return Model matrix for the whole Mesh
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

	/// \brief Cube vertices
	static const GLfloat vertices[];
	/// \brief Cube face indices
	static const GLint indices[];

	/// \brief Mesh original state
	State start;

	/// \brief Root cube of the Mesh
	Cube* root;
	/// \brief World position of the Mesh
	glm::vec3 position;
	/// \brief Size of the Mesh
	glm::vec3 size;
	/// \brief Scale factor of the Mesh
	float scaleFactor;
	/// \brief Y rotation of the Mesh, in degrees
	float yRot;
	/// \brief Z rotation of the Mesh, in degrees
	float zRot;

	/// \brief Giving friend access to the MeshParser class
	friend class MeshParser;
	///\brief Set input callback function as friend
	friend void key_callback(GLFWwindow*, int, int, int, int);
};
