#pragma once

#include "Parser.h"

class FileParser : public Parser<std::string>
{
public:
	~FileParser();
	std::string parseAll() const override;
};