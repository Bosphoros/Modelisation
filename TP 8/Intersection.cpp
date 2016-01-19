#include "Intersection.h"



Intersection::Intersection()
{
}

Intersection::Intersection(Operators * o1, Operators * o2) : op1(o1), op2(o2)
{
}


Intersection::~Intersection()
{
}

bool Intersection::isInside(point3 & p)
{
	return op1->isInside(p) || op2->isInside(p);
}

float Intersection::minExtentX()
{
	return std::fmin(op1->minExtentX(), op2->minExtentX());
}

float Intersection::maxExtentX()
{
	return std::fmax(op1->maxExtentX(), op2->maxExtentX());
}

float Intersection::minExtentY()
{
	return std::fmin(op1->minExtentY(), op2->minExtentY());
}

float Intersection::maxExtentY()
{
	return std::fmax(op1->maxExtentY(), op2->maxExtentY());
}

float Intersection::minExtentZ()
{
	return std::fmin(op1->minExtentZ(), op2->minExtentZ());
}

float Intersection::maxExtentZ()
{
	return std::fmax(op1->maxExtentZ(), op2->maxExtentZ());
}
