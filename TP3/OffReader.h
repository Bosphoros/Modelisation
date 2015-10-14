#pragma once
#include "Mesh.h"
class OffReader
{
public:
	OffReader();

	Mesh import(std::string file);

	~OffReader();
};

