#include "MyLine.h"

MyLine::MyLine(double x, double y, double z, double x2, double y2, double z2)
	: DrawableObject(x, y, z), pt2(x2, y2, z2)
{
}

MyLine::MyLine(double x2, double y2, double z2)
	: DrawableObject(0.0, 0.0, 0.0), pt2(x2, y2, z2)
{
}

void MyLine::draw() const
{
	glDisable(GL_LIGHTING);
	glColor3d(1.0, 0.0, 1.0);
	glBegin(GL_LINES);
	{
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(pt2.x, pt2.y, pt2.z);
	}
	glEnd();
	glEnable(GL_LIGHTING);
}