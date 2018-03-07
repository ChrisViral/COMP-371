#pragma once

#include <string>

/**
 * \brief    Parser abstract class
 * \tparam T The type of object to be parsed
 */
template <class T>
class Parser
{
public:

	/**
	 * \brief Default constructor, no file location stored
	 */
	Parser();
	/**
	 * \brief Creates a parser looking at a specified file
	 * \param location File location to parse
	 */
	explicit Parser(const std::string location);
	/**
	 * \brief Default destructor
	 */
	virtual ~Parser() = 0;

	/**
	  * \brief Parses the file into the given object type and returns it
	  * \return Parsed object
	  */
	 virtual T parseAll() const = 0;

protected:

	/// \brief Parser file location
	const std::string location;
};
