#include <fstream>
#include <iostream>
#include <vector>
#include "MeshParser.h"
#include "TextUtils.hpp"

using namespace TextUtils;

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;

MeshParser::MeshParser(const string location) : Parser(location) { }

MeshParser::~MeshParser() { }

Mesh* MeshParser::parse() const
{
	ifstream f;
	//Set exception bits
	f.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		f.open(location);

		string line;
		int l = 0;
		//Skip heading empty and comment lines
		while (getline(f, line) && ignoreLine(line)) { l++; }

		//If the first text line is not a mesh declaration, exit now
		if (line != "[Mesh]")
		{
			cout << "ERROR::MESH_PARSER::FILE_NOT_CORRECTLY_FORMATTED";
			return nullptr;
		}

		Mesh* mesh = new Mesh();
		while (getline(f, line))
		{
			l++;
			if (ignoreLine(line)) { continue; }
			if (line == "[Cube]") { break; }

			vector<string> splits = split(line, "=");
			if (splits.size() != 2)
			{
				cout << "Invalid data at line " << l << endl;
				continue;
			}

			string name = splits[0];
			//TODO: switch between possible values
		}

		vector<Cube*> cubes;
		while (getline(f, line))
		{
			l++;
			if (ignoreLine(line)) { continue; }

			vector<string> splits = split(line, "=");
			if (splits.size() != 2)
			{
				cout << "Invalid data at line " << l << endl;
				continue;
			}

			string name = splits[0];
			//TODO: switch between possible values
		}
		return mesh;
	}
	catch (ifstream::failure e)
	{
		//If error happens, print out error then return empty string
		cout << "ERROR::MESH_PARSER::FILE_NOT_SUCCESFULLY_READ\n" << e.what() << endl;
		return nullptr;
	}
}
