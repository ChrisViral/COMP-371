// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

#pragma once
#include "Parser.h"
#include "../Objects/Mesh.h"

/**
 * \brief Mesh file parser implementation
 */
class MeshParser : public Parser<Mesh*>
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new MeshParser at the given file location
	 * \param location 
	 */
	explicit MeshParser(const std::string location);
	/**
	 * \brief Frees up allocated memory
	 */
	~MeshParser();

	//Methods
	/**
	 * \brief Pareses the whole file to a Mesh object
	 * \return Pointer to the created Mesh object. This object is on the heap and the calling object assumes ownership of this reference
	 */
	Mesh* parse() const override;

private:
	//Structures
	/**
	 * \brief Parent/child link prototype
	 */
	struct Link
	{
		/// \brief Name of the parent
		std::string parent;
		///\brief Pointer to the child
		Cube* child;
	};

	//Constants
	static const std::string sep;

	//Static methods
	/**
	 * \brief Finds a cube of the given name within the passed vector
	 * \param cubes Vector of all cubes to search within
	 * \param name  Name of the Cube to find
	 * \return		The pointer to the found cube, or nullptr if none was found
	 */
	static Cube* findCube(std::vector<Cube*>& cubes, const std::string& name);
};
