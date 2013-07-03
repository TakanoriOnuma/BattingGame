#include "Rectangle2D.h"

Rectangle2D::Rectangle2D(double width, double height)
	: DrawableObject(), width(width), height(height), color()
{
}

Rectangle2D::Rectangle2D(double width, double height, const ColorData& color)
	: DrawableObject(), width(width), height(height), color(color)
{
}

Rectangle2D::Rectangle2D(double x, double y, double z, double width, double height, const ColorData& color)
	: DrawableObject(x, y, z), width(width), height(height), color(color)
{
}

void Rectangle2D::draw() const
{
	glDisable(GL_LIGHTING);

	const double half_width  = width / 2;
	const double half_height = height / 2;

	glEnable(GL_BLEND);
	glColor4d(0.0, 0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	{
		glVertex3d(-half_width + 0.01, -half_height + 0.01, 0);
		glVertex3d( half_width - 0.01, -half_height + 0.01, 0);
		glVertex3d( half_width - 0.01,  half_height - 0.01, 0);
		glVertex3d(-half_width + 0.01,  half_height - 0.01, 0);
	}
	glEnd();
	glDisable(GL_BLEND);

	glBegin(GL_LINE_LOOP);
	glColor3d(color.red, color.green, color.blue);
	{
		glVertex3d(-half_width, -half_height, 0);
		glVertex3d( half_width, -half_height, 0);
		glVertex3d( half_width,  half_height, 0);
		glVertex3d(-half_width,  half_height, 0);
	}
	glEnd();

	glEnable(GL_LIGHTING);
}