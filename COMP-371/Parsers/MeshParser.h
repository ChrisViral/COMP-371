#pragma once
#include "Parser.h"
#include "../Objects/Mesh.h"

class MeshParser : public Parser<Mesh*>
{
public:
	explicit MeshParser(const std::string location);
	~MeshParser();

	Mesh* parse() const override;

private:
	struct Link
	{
		std::string parent;
		Cube* child;
	};

	const std::string sep = "=";

	static Cube* findCube(std::vector<Cube*>& cubes, const std::string& name);
};
