#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

/**
 * \brief Namespace containing some useful string manipulation methods
 */
namespace TextUtils
{
	//Constants
	/// \brief Comment indicating string
	const std::string COMMENT = "//";

	//Methods
	/**
	 * \brief Determines if the string is empty
	 * \param text String to test
	 * \return True if the string is of size 0, false otherwise
	 */
	bool isEmpty(const std::string text);
	/**
	 * \brief Splits the given string at all occurences of the passed delimiter
	 * \param text		String to split
	 * \param delimiter String delimiter
	 * \return			A vector containing all the splits. If the delimiter was of size 0, the vector will contain the full string once
	 *					Empty strings may be results of the splitting operation and will be in the vector as well.
	 */
	std::vector<std::string> split(std::string text, const std::string delimiter);
	/**
	 * \brief Removes any comments from a given string
	 * \param text String to remove comments from
	 * \return	   The string with removed comments. May be of size 0
	 */
	std::string stripComment(const std::string text);
	/**
	 * \brief Trims the string at start and end, removing all white spaces
	 * \param text String to trim
	 * \return	   The trimmed text. May be of size 0
	 */
	std::string& trim(std::string &text);
	/**
	 * \brief Parses a comma separated vector of three floats
	 * \param text String to parse
	 * \return The resulting vector
	 */
	glm::vec3 parseVec3(const std::string text);
}