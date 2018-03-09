#pragma once
#include "Parser.h"
#include "../Objects/Mesh.h"

class MeshParser : public Parser<Mesh*>
{
public:
	explicit MeshParser(const std::string location);
	~MeshParser();

	Mesh* parse() const override;
};
