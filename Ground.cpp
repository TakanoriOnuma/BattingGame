#include "OpenGL.h"

#include "Ground.h"
#include "MyLine.h"

const float Ground::ground[2][4] = {
	{ 0.6f, 0.6f, 0.6f, 1.0f },
	{ 0.3f, 0.3f, 0.3f, 1.0f },
};

Ground::Ground(int width, int distance)
	: DrawableObject(), width(width), distance(distance)
{
	init();
}

Ground::Ground(double x, double y, double z, int width, int distance)
	: DrawableObject(x, y, z), width(width), distance(distance)
{
	init();
}

Ground::~Ground()
{
	delete line1;
	delete line2;
}

void Ground::init()
{
	rectBox.setRectBox(distance, width, 0.0);
	line1 = new MyLine(1.0, 0.01, 23.0, 17.5, 0.01, -52.5);
	line2 = new MyLine(-1.0, 0.01, 23.0, -17.5, 0.01, -52.5);
}

void Ground::draw() const
{
	line1->draw(true, true);
	line2->draw(true, true);
	glNormal3d(0.0, 1.0, 0.0);
	for(int j = -distance / 2; j < distance / 2; j++){
		for(int i = -width / 2; i < width / 2; i++){
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
			glBegin(GL_QUADS);
			{
				glVertex3d((GLdouble)i, 0.0, (GLdouble)j);
				glVertex3d((GLdouble)i, 0.0, (GLdouble)(j + 1));
				glVertex3d((GLdouble)(i + 1), 0.0, (GLdouble)(j + 1));
				glVertex3d((GLdouble)(i + 1), 0.0, (GLdouble)j);
			}
			glEnd();
		}
	}
}