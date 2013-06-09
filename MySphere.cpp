#include "OpenGL.h"

#include "MySphere.h"

MySphere::MySphere(double radius, int sides)
	: DrawObject(), radius(radius), sides(sides)
{
	init();
}

MySphere::MySphere(double x, double y, double z, double radius, int sides)
	: DrawObject(x, y, z), radius(radius), sides(sides)
{
	init();
}

void MySphere::init()
{
	double diameter = 2 * radius;
	rectParallel.setRectangularParallelepiped(diameter, diameter, diameter);
}

void MySphere::draw() const
{
	GLUquadric* quad = quadObject.getQuadric();

//	gluQuadricNormals(quad, GL_SMOOTH);
	gluSphere(quad, radius, sides, sides);
}