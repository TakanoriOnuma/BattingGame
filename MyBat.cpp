#include "OpenGL.h"

#include "MyBat.h"

MyBat::MyBat(double x, double y, double z)
	: DrawableObject(x, y, z)
{
	init();
}

MyBat::MyBat(const Point3d& pt)
	: DrawableObject(pt)
{
	init();
}

void MyBat::init()
{
	rectBox.setRectBox(0.4, 0.4, 2.3);
}

void MyBat::draw() const
{
	GLUquadric* quad = quadObject.getQuadric();

	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluDisk(quad, 0.0, 0.18, 16, 16);

	glTranslated(0.0, 0.0, -0.1);
	gluCylinder(quad, 0.2, 0.18, 0.1, 16, 1);

	glTranslated(0.0, 0.0, -0.6);
	gluCylinder(quad, 0.2, 0.2, 0.6, 16, 1);

	glTranslated(0.0, 0.0, -0.9);
	gluCylinder(quad, 0.1, 0.2, 0.9, 16, 1);

	glTranslated(0.0, 0.0, -0.6);
	gluCylinder(quad, 0.1, 0.1, 0.6, 16, 1);

	gluDisk(quad, 0.1, 0.15, 16, 16);

	glTranslated(0.0, 0.0, -0.1);
	gluCylinder(quad, 0.15, 0.15, 0.1, 16, 1);

	gluQuadricOrientation(quad, GLU_INSIDE);
	gluDisk(quad, 0.0, 0.15, 16, 1);

	glTranslated(-0.2, -0.2, 0.0);
}