#include <algorithm>
#include <cctype>
#include <locale>
#include "TextUtils.hpp"
#include "MeshParser.h"

using glm::vec3;
using std::find_if;
using std::isspace;
using std::to_string;
using std::stof;
using std::string;
using std::vector;

bool TextUtils::isEmpty(const string line)
{
	//Test against 0
	return line.length() == 0;
}

vector<string> TextUtils::split(string text, const string delimiter)
{
	//Get delimiter length
	vector<string> splits;
	const size_t len = delimiter.length();
	//If length zero, just add the string to the vector
	if (len == 0) { splits.push_back(text); }
	else
	{
		//Repetitively find the next occurance and get the substring
		size_t front = 0;
		for (size_t pos = text.find(delimiter); pos != string::npos; front = pos + len, pos = text.find(delimiter, front))
		{
			splits.push_back(text.substr(front, pos - front));
		}
		//Push the final substring
		splits.push_back(text.substr(front, text.length() - front));
	}
	//Return the result
	return splits;
}

string TextUtils::stripComment(const string text)
{
	//Find the comment position
	const size_t pos = text.find(COMMENT);
	//Substring if found
	return pos == string::npos ? text : text.substr(0, pos);
}

string& TextUtils::trim(string &text)
{
	//Erase heading and trailing spaces
	text.erase(text.begin(), find_if(text.begin(), text.end(), [](int c) { return !isspace(c); }));
	text.erase(find_if(text.rbegin(), text.rend(), [](int c) { return !isspace(c); }).base(), text.end());
	return text;
}

vec3 TextUtils::parseVec3(const string text)
{
	//Split line
	vector<string> splits = split(text, ",");
	//If not of size 3, invalid format
	if (splits.size() != 3) { throw std::invalid_argument("Vector3 parse has incorrect amount of elements (" + to_string(splits.size()) + ")"); }
	//Parse floats
	return vec3(stof(trim(splits[0])), stof(trim(splits[1])), stof(trim(splits[2])));
}


