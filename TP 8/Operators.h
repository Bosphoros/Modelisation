#pragma once
#include "struct.h"

class Operators
{
public:
	Operators();
	~Operators();
	bool virtual isInside(point3& p) = 0;
	float virtual minExtentX() = 0;
	float virtual maxExtentX() = 0;
	float virtual minExtentY() = 0;
	float virtual maxExtentY() = 0;
	float virtual minExtentZ() = 0;
	float virtual maxExtentZ() = 0;
};

