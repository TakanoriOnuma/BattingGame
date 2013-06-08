#include "OpenGL.h"

#include "MySphere.h"

MySphere::MySphere(double radius, int sides)
	: DrawObject(), radius(radius), sides(sides)
{
}

MySphere::MySphere(double x, double y, double z, double radius, int sides)
	: DrawObject(x, y, z), radius(radius), sides(sides)
{
}

void MySphere::draw() const
{
	GLUquadric* quad = quadObject.getQuadric();

//	gluQuadricNormals(quad, GL_SMOOTH);
	gluSphere(quad, radius, sides, sides);
}