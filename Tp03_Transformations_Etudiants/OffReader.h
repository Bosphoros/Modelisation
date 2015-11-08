#pragma once
#include "Mesh.h"
class OffReader
{
public:
	OffReader();

	Mesh import(std::string file);
	void export(const Mesh &m, std::string file);

	~OffReader();
};

