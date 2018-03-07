#pragma once

#include "Parser.h"

class FileParser : public Parser<std::string>
{
public:
	explicit FileParser(const std::string location);
	~FileParser();
	std::string parse() const override;
};