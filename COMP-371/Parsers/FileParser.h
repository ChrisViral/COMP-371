// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

#pragma once

#include "Parser.h"

/**
 * \brief Basic file parse implementation
 */
class FileParser : public Parser<std::string>
{
public:
	//Constructors/Destructors
	/**
	 * \brief Creates a new FileParser at the given file location
	 * \param location Location of the file to parse
	 */
	explicit FileParser(const std::string location);
	/**
	 * \brief Frees up allocated memory
	 */
	~FileParser();

	//Methods
	/**
	 * \brief Parses the whole file as a string
	 * \return String of the whole file
	 */
	std::string parse() const override;
};