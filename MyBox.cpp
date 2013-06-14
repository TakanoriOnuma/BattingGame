#include "MyBox.h"
#include "MaterialData.h"

int MyBox::face[6][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 },
};

GLdouble MyBox::normal[6][3] = {
	{  0.0,  0.0, -1.0 },
	{  1.0,  0.0,  0.0 },
	{  0.0,  0.0,  1.0 },
	{ -1.0,  0.0,  0.0 },
	{  0.0, -1.0,  0.0 },
	{  0.0,  1.0,  0.0 },
};

MyBox::MyBox(const Point3d& pt, double length, double width, double height)
	: DrawObject(pt), length(length), width(width), height(height)
{
	init();
}

MyBox::MyBox(GLdouble x, GLdouble y, GLdouble z, double length, double width, double height)
	: DrawObject(x, y, z), length(length), width(width), height(height)
{
	init();
}

void MyBox::init()
{
	GLdouble hx = width * 0.5;
	GLdouble hz = length * 0.5;

	vertex[0][0] = -hx;		vertex[0][1] = -height;		vertex[0][2] = -hz;
	vertex[1][0] =  hx;		vertex[1][1] = -height;		vertex[1][2] = -hz;
	vertex[2][0] =  hx;		vertex[2][1] =     0.0;		vertex[2][2] = -hz;
	vertex[3][0] = -hx;		vertex[3][1] =     0.0;		vertex[3][2] = -hz;
	vertex[4][0] = -hx;		vertex[4][1] = -height;		vertex[4][2] =  hz;
	vertex[5][0] =  hx;		vertex[5][1] = -height;		vertex[5][2] =  hz;
	vertex[6][0] =  hx;		vertex[6][1] =     0.0;		vertex[6][2] =  hz;
	vertex[7][0] = -hx;		vertex[7][1] =     0.0;		vertex[7][2] =  hz;

	rectBox.setRectBox(length, width, height);
}

void MyBox::draw() const
{
	glBegin(GL_QUADS);
	for(int j = 0; j < 6; j++){
		glNormal3dv(normal[j]);
		for(int i = 3; i >= 0; i--){
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
}