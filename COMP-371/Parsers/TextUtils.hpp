#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace TextUtils
{
	const std::string COMMENT = "//";

	bool isEmpty(const std::string line);
	std::vector<std::string> split(std::string text, const std::string delimiter);
	std::string stripComment(const std::string text);
	std::string& trim(std::string &text);
	glm::vec3 parseVec3(const std::string text);
}