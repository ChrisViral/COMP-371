#pragma once

#include <string>
#include <vector>

namespace TextUtils
{
	const std::string COMMENT = "//";

	bool ignoreLine(const std::string line);
	std::vector<std::string> split(std::string line, const std::string delimiter);
}