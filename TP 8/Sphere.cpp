#include "Sphere.h"



Sphere::Sphere()
{
}


Sphere::Sphere(point3 & c, float r) : center(c), radius(r)
{
}

Sphere::~Sphere()
{
}

bool Sphere::isInside(point3 & p)
{
	return p.distToPoint(center) <= radius;
}

float Sphere::minExtentX()
{
	return center.x - radius;
}

float Sphere::maxExtentX()
{
	return center.x + radius;
}

float Sphere::minExtentY()
{
	return center.y - radius;
}

float Sphere::maxExtentY()
{
	return center.y + radius;
}

float Sphere::minExtentZ()
{
	return center.z - radius;
}

float Sphere::maxExtentZ()
{
	return center.z + radius;
}
