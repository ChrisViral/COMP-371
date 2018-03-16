// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include "MeshParser.h"
#include "TextUtils.hpp"

using namespace TextUtils;

using std::cout;
using std::endl;
using std::getline;
using std::stof;
using std::ifstream;
using std::stack;
using std::string;
using std::vector;
using glm::vec3;

const string MeshParser::sep = "=";

MeshParser::MeshParser(const string location) : Parser(location) { }

MeshParser::~MeshParser() { }

Mesh* MeshParser::parse() const
{
	//Set exception bits
	ifstream f;
	f.exceptions(ifstream::badbit);

	//Header message
	cout << "Parsing Mesh file: " << location << endl;
	try
	{
		//Open file
		f.open(location);

		string line; //Line text
		int num = 0; //Line number
		//Skip heading empty and comment lines
		while (getline(f, line) && isEmpty(stripComment(trim(line)))) { num++; }

		//If the first text line is not a mesh declaration, exit now
		if (line != "[Mesh]")
		{
			cout << "ERROR::MESH_PARSER::FILE_NOT_CORRECTLY_FORMATTED";
			return nullptr;
		}

		//Setup mesh
		string rootName;
		Mesh* mesh = new Mesh();

		//Loop through all lines
		while (getline(f, line))
		{
			num++;							 //Increment line number
			line = stripComment(line);		 //Remove comments
			trim(line);						 //Trim line
			if (isEmpty(line)) { continue; } //Ignore empty lines
			if (line == "[Cube]") { break; } //Cube encountered, continue

			//Split at separator
			vector<string> splits = split(line, sep);
			//Check if there are a valid number of splits
			if (splits.size() != 2)
			{
				cout << "Invalid separators at line " << num << endl;
				continue;
			}

			//Trim current line values
			const string name = trim(splits[0]);
			const string value = trim(splits[1]);
			//Find correct value
			if (name == "root")
			{
				rootName = value;
			}
			else if (name == "position")
			{
				mesh->position = parseVec3(value);
			}
			else if (name == "size")
			{
				mesh->size = vec3(stof(value));
			}
			else if(name == "yRot")
			{
				mesh->yRot = stof(value);
			}
			else if (name == "zRot")
			{
				mesh->zRot = stof(value);
			}
			else
			{
				//Not found, mention error and line number
				cout << "Invalid value format at line " << num << endl;
			}
		}
		
		//Setup cube parsing
		string parent = "";
		Cube* cube = new Cube(mesh);
		vector<Link> links;
		vector<Cube*> cubes;

		//Loop through lines
		while (getline(f, line))
		{
			num++;							 //Increment line number
			line = stripComment(line);		 //Remove comment if any
			trim(line);						 //Trim line
			if (isEmpty(line)) { continue; } //Ignore empty lines

			//If new cube declaration, wrap up previous cube and store
			if (line == "[Cube]")
			{
				//Setup and push link data
				Link link;
				link.parent = parent;
				link.child = cube;
				links.push_back(link);
				//Push cube
				cubes.push_back(cube);
				//Reset cube
				cube = new Cube(mesh);
				continue;
			}

			//Split at separator
			vector<string> splits = split(line, sep);
			//Check if there are a valid number of splits
			if (splits.size() != 2)
			{
				cout << "Invalid separators at line " << num << endl;
				continue;
			}

			//Trim current line values
			const string name = trim(splits[0]);
			const string value = trim(splits[1]);
			//Find correct value
			if (name == "name")
			{
				cube->name = value;
			}
			else if (name == "parent")
			{
				parent = value;
			}
			else if (name == "colour")
			{
				cube->colour = vec3(stof(value));
			}
			else if (name == "position")
			{
				cube->position = parseVec3(value);
			}
			else if (name == "size")
			{
				cube->size = parseVec3(value);
			}
			else if (name == "offset")
			{
				cube->offset = parseVec3(value);
			}
			else if (name == "angle")
			{
				cube->angle = stof(value);
				cube->startAngle = cube->angle;
			}
			else
			{
				//Not found, mention error and line number
				cout << "Invalid value format at line " << num << endl;
			}
		}
		//Add final child
		Link link;
		link.parent = parent;
		link.child = cube;
		links.push_back(link);
		cubes.push_back(cube);
		cube = nullptr;

		//Set all links
		for (Link& l : links)
		{
			//If root node, set it as such
		    if (l.child->name == rootName) { mesh->root = l.child; }
			else
			{
				//Find parent cube
				Cube* p = findCube(cubes, l.parent);
				//Fail if parent not found
				if (p == nullptr)
				{
					cout << "ERROR::MESH_PARSER::PARENT_NOT_FOUND\nChild name: " << l.child->name << endl;
					return nullptr;
				}
				//Setup parent/children link
				l.child->parent = p;
				p->children.push_back(l.child);
			}
		}

		//Make sure the root is set
		if (mesh->root == nullptr)
		{
			cout << "ERROR::MESH_PARSER::ROOT_NOT_FOUND\nTarget root: " << rootName << endl;
			return nullptr;
		}

		//Make sure all cubes have a parent
		for (Cube* c : cubes)
		{
			if (c->name != rootName && c->parent == nullptr)
			{
				cout << "ERROR::MESH_PARSER::NOT_ALL_PARENTS_SET\nCube name: " << c->name << endl;
				return nullptr;
			}
		}

		//Make sure the cubes form a hierarchical tree structure (avoiding multiple/circular trees)
		int count = 0;
		stack<Cube*> search;
		search.push(mesh->root);

		//DFS the mesh and count cubes
		while (!search.empty())
		{
			count++;				//Increment counter
			Cube* c = search.top();	//Get top element
			search.pop();			//Pop top element

			//Add all children
			for (Cube* child : c->children)
			{
				search.push(child);
			}
		}

		//If search count is different from total cubes, there is a separate or circular tree somewhere
		if (count != cubes.size())
		{
			cout << "ERROR::MESH_PARSER::INVALID_MESH_STRUCTURE" << endl;
			return nullptr;
		}

		//Wrap up and return
		cout << "File successfully parsed, " << cubes.size() << " cubes detected." << endl;
		cubes.clear();
		return mesh;
	}
	//If an error happens, print out error then return empty string
	catch (ifstream::failure e)
	{
		cout << "ERROR::MESH_PARSER::FILE_NOT_SUCCESFULLY_READ\n" << e.what() << endl;
		return nullptr;
	}
	catch (std::invalid_argument e)
	{
		cout << "ERROR::MESH_PARSER::FLOAT_PARSE_FAILED\n" << e.what() << endl;
		return nullptr;
	}
}

Cube* MeshParser::findCube(vector<Cube*>& cubes, const string& name)
{
	//Loop through cubes
	for (Cube* c : cubes)
	{
		//Return if name matches
		if (c->name == name)
		{
			return c;
		}
	}

	//Otherwise return null pointer
	return nullptr;
}
