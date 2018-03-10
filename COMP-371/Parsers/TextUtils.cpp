#include <algorithm>
#include <cctype>
#include <locale>
#include "TextUtils.hpp"
#include "MeshParser.h"

using glm::vec3;
using std::find_if;
using std::isspace;
using std::stof;
using std::string;
using std::vector;

bool TextUtils::isEmpty(const string line)
{
	return line.length() == 0;
}

vector<string> TextUtils::split(string text, const string delimiter)
{
	vector<string> splits;
	if (delimiter.length() == 0) { splits.push_back(text); }
	else
	{
		for (size_t pos = text.find(delimiter); pos != string::npos; pos = text.find(delimiter))
		{
			splits.push_back(text.substr(0, pos));
			text.erase(0, pos + delimiter.length());
		}
	}
	return splits;
}

string TextUtils::stripComment(const string text)
{
	return split(text, COMMENT)[0];
}

string& TextUtils::trim(string &text)
{
	text.erase(text.begin(), find_if(text.begin(), text.end(), [](int c) { return !isspace(c); }));
	text.erase(find_if(text.rbegin(), text.rend(), [](int c) { return isspace(c); }).base(), text.end());
	return text;
}

vec3 TextUtils::parseVec3(const string text)
{
	vector<string> splits = split(text, ",");
	if (splits.size() != 3) { throw std::invalid_argument("Vector3 parse has incorrect amount of elements (" + std::to_string(splits.size()) + ")"); }
	return vec3(stof(trim(splits[0])), stof(trim(splits[1])), stof(trim(splits[2])));
}


