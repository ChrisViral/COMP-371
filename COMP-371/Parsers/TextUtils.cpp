#include "TextUtils.hpp"
#include "MeshParser.h"

using TextUtils::COMMENT;
using std::string;
using std::vector;

bool TextUtils::ignoreLine(const string line)
{
	return line.length() == 0 || (line.length() >= COMMENT.length() && line.compare(0, COMMENT.length(), COMMENT) == 0);
}

vector<string> TextUtils::split(string line, const string delimiter)
{
	vector<string> splits;
	for (size_t pos = line.find(delimiter); pos != string::npos; pos = line.find(delimiter))
	{
		splits.push_back(line.substr(0, pos));
		line.erase(0, pos + delimiter.length());
	}
	return splits;
}
