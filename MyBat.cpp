#include "OpenGL.h"

#include "MyBat.h"

MyBat::MyBat(double x, double y, double z)
	: DrawObject(x, y, z)
{
	init();
}

MyBat::MyBat(const Point3d& pt)
	: DrawObject(pt)
{
	init();
}

void MyBat::init()
{
	rectBox.setRectBox(0.2, 0.2, 2.6);
}

void MyBat::draw() const
{
	GLUquadric* quad = quadObject.getQuadric();

	glPushMatrix();

	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluDisk(quad, 0.0, 0.18, 16, 16);

	glTranslated(0.0, 0.0, -0.1);
	gluCylinder(quad, 0.2, 0.18, 0.1, 16, 1);

	glTranslated(0.0, 0.0, -0.7);
	gluCylinder(quad, 0.2, 0.2, 0.7, 16, 1);

	glTranslated(0.0, 0.0, -1.0);
	gluCylinder(quad, 0.1, 0.2, 1.0, 16, 1);

	glTranslated(0.0, 0.0, -0.7);
	gluCylinder(quad, 0.1, 0.1, 0.7, 16, 1);

	gluDisk(quad, 0.1, 0.15, 16, 16);

	glTranslated(0.0, 0.0, -0.1);
	gluCylinder(quad, 0.15, 0.15, 0.1, 16, 1);

	gluQuadricOrientation(quad, GLU_INSIDE);
	gluDisk(quad, 0.0, 0.15, 16, 1);

	glPopMatrix();
}