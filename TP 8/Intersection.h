#pragma once
#include "Operators.h"
class Intersection :
	public Operators
{
public:
	Operators* op1;
	Operators* op2;
	Intersection();
	Intersection(Operators* o1, Operators* o2);
	~Intersection();

	// H�rit� via Operators
	virtual bool isInside(point3 & p) override;
	virtual float minExtentX() override;
	virtual float maxExtentX() override;
	virtual float minExtentY() override;
	virtual float maxExtentY() override;
	virtual float minExtentZ() override;
	virtual float maxExtentZ() override;
};

