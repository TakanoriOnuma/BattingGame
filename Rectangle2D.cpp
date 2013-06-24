#include "Rectangle2D.h"

Rectangle2D::Rectangle2D(double width, double height)
	: DrawObject(), width(width), height(height), color()
{
}

Rectangle2D::Rectangle2D(double width, double height, const ColorData& color)
	: DrawObject(), width(width), height(height), color(color)
{
}

Rectangle2D::Rectangle2D(double x, double y, double z, double width, double height, const ColorData& color)
	: DrawObject(x, y, z), width(width), height(height), color(color)
{
}

void Rectangle2D::draw() const
{
	glDisable(GL_LIGHTING);

	const Point3d& pt = getPoint();
	const double half_width  = width / 2;
	const double half_height = height / 2;

	glBegin(GL_LINE_LOOP);
	glColor3d(color.red, color.green, color.blue);
	{
		glVertex3d(pt.x - half_width, pt.y - half_height, pt.z);
		glVertex3d(pt.x + half_width, pt.y - half_height, pt.z);
		glVertex3d(pt.x + half_width, pt.y + half_height, pt.z);
		glVertex3d(pt.x - half_width, pt.y + half_height, pt.z);
	}
	glEnd();

	glEnable(GL_LIGHTING);
}