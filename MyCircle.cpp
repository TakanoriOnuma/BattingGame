#include "OpenGL.h"

#include "MyCircle.h"
#include "TriFunction.h"

MyCircle::MyCircle(double radius)
	: DrawableObject(), radius(radius), color()
{
}

MyCircle::MyCircle(double radius, const ColorData& color)
	: DrawableObject(), radius(radius), color(color)
{
}

MyCircle::MyCircle(double x, double y, double z, double radius, const ColorData& color)
	: DrawableObject(x, y, z), radius(radius), color(color)
{
}

void MyCircle::draw() const
{
	glDisable(GL_LIGHTING);

	TriFunction& triFunc = TriFunction::getInstance();
	glColor4d(color.red, color.green, color.blue, color.alpha);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < 360; i++){
		glVertex3d(radius * triFunc.t_cos(i), radius * triFunc.t_sin(i), 0.0);
	}
	glEnd();

	glEnable(GL_LIGHTING);
}