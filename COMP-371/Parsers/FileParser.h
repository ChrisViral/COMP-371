#pragma once

#include "Parser.h"

class FileParser : public Parser<std::string>
{
	~FileParser();
	std::string parseAll() const override;
};