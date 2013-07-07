#include "OpenGL.h"

#include "RectBox.h"

const int RectBox::edge[12][2] = {
	{ 0, 1 },
	{ 1, 2 },
	{ 2, 3 },
	{ 3, 0 },
	{ 4, 5 },
	{ 5, 6 },
	{ 6, 7 },
	{ 7, 4 },
	{ 0, 4 },
	{ 1, 5 },
	{ 2, 6 },
	{ 3, 7 },
};

RectBox::RectBox()
	: width(0.0), length(0.0), height(0.0)
{
}

RectBox::RectBox(double length, double width, double height)
	: length(length), width(width), height(height)
{
}

void RectBox::draw() const
{
	GLdouble vertex[][3] = {
		{   0.0,    0.0,    0.0 },
		{ width,    0.0,    0.0 },
		{ width, length,    0.0 },
		{   0.0, length,    0.0 },
		{   0.0,    0.0, height },
		{ width,    0.0, height },
		{ width, length, height },
		{   0.0, length, height },
	};


	glDisable(GL_LIGHTING);
	glColor3d(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	for(int i = 0; i < 12; i++){
		glVertex3dv(vertex[edge[i][0]]);
		glVertex3dv(vertex[edge[i][1]]);
	}
	glEnd();
	glEnable(GL_LIGHTING);
}