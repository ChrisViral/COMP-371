#include "Parser.h"

using std::string;

template <class T>
Parser<T>::Parser() : location("") { }

template <class T>
Parser<T>::Parser(const string location) : location(location) { }

template <class T>
Parser<T>::~Parser() { }

template <class T> T Parser<T>::parseAll() const
{
	throw std::runtime_error("No parser available for this type");
}
