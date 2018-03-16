// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#include <fstream>
#include <iostream>
#include <sstream>
#include "FileParser.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;
using std::string;

FileParser::FileParser(const string location) : Parser(location) { }

FileParser::~FileParser() { }

string FileParser::parse() const
{
	//Set exception bits
	ifstream f;
	f.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		//Open file
		f.open(location);

		//Read to string buffer
		stringstream ss;
		ss << f.rdbuf();

		//Convert to string
		string s = ss.str();
		return s.c_str();
	}
	catch (ifstream::failure e)
	{
		//If error happens, print out error then return empty string
		cout << "ERROR::FILE_PARSER::FILE_NOT_SUCCESFULLY_READ\nFile: " << location << endl << e.what() << endl;
		return "";
	}
}
