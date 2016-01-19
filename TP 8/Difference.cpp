#include "Difference.h"



Difference::Difference()
{
}

Difference::Difference(Operators * o1, Operators * o2) : op1(o1), op2(o2)
{
}


Difference::~Difference()
{
}

bool Difference::isInside(point3 & p)
{
	return op1->isInside(p) && !op2->isInside(p);
}

float Difference::minExtentX()
{
	return std::fmin(op1->minExtentX(), op2->minExtentX());
}

float Difference::maxExtentX()
{
	return std::fmax(op1->maxExtentX(), op2->maxExtentX());
}

float Difference::minExtentY()
{
	return std::fmin(op1->minExtentY(), op2->minExtentY());
}

float Difference::maxExtentY()
{
	return std::fmax(op1->maxExtentY(), op2->maxExtentY());
}

float Difference::minExtentZ()
{
	return std::fmin(op1->minExtentZ(), op2->minExtentZ());
}

float Difference::maxExtentZ()
{
	return std::fmax(op1->maxExtentZ(), op2->maxExtentZ());
}
