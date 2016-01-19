#pragma once
#include "Operators.h"
#include "struct.h"
class Sphere :
	public Operators
{
public:
	point3 center;
	float radius;

	Sphere();
	Sphere(point3& c, float r);
	~Sphere();

	// Hérité via Operators
	virtual bool isInside(point3 & p) override;


	// Hérité via Operators
	virtual float minExtentX() override;

	virtual float maxExtentX() override;

	virtual float minExtentY() override;

	virtual float maxExtentY() override;

	virtual float minExtentZ() override;

	virtual float maxExtentZ() override;

};

