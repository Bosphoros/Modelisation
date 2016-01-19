#include "Union.h"



Union::Union()
{
}

Union::Union(Operators * o1, Operators * o2) : op1(o1), op2(o2)
{
}


Union::~Union()
{
}

bool Union::isInside(point3 & p)
{
	return op1->isInside(p) || op2->isInside(p);
}

float Union::minExtentX()
{
	return std::fmin(op1->minExtentX(), op2->minExtentX());
}

float Union::maxExtentX()
{
	return std::fmax(op1->maxExtentX(), op2->maxExtentX());
}

float Union::minExtentY()
{
	return std::fmin(op1->minExtentY(), op2->minExtentY());
}

float Union::maxExtentY()
{
	return std::fmax(op1->maxExtentY(), op2->maxExtentY());
}

float Union::minExtentZ()
{
	return std::fmin(op1->minExtentZ(), op2->minExtentZ());
}

float Union::maxExtentZ()
{
	return std::fmax(op1->maxExtentZ(), op2->maxExtentZ());
}
