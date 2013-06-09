#include "OpenGL.h"

#include "MyCylinder.h"

MyCylinder::MyCylinder(double radius, double height, int sides)
	: DrawObject(), radius(radius), height(height), sides(sides)
{
	init();
}

MyCylinder::MyCylinder(double x, double y, double z, double radius, double height, int sides)
	: DrawObject(x, y, z), radius(radius), height(height), sides(sides)
{
	init();
}

void MyCylinder::init()
{
	double diameter = 2 * radius;
	rectParallel.setRectangularParallelepiped(diameter, diameter, height);
}

void MyCylinder::draw() const
{
	GLUquadric* quad = quadObject.getQuadric();
	double half_height = height / 2;

	/* –Ê‚Ì“h‚è‚Â‚Ô‚µ‚ğw’è‚·‚é(ü‰æ‚Å‚Í‚È‚­‰A‰e‚ğ‚Â‚¯‚½‰~’Œ‚ğ•`‚­) */
	gluQuadricNormals(quad, GLU_SMOOTH);

	glPushMatrix();				// •ÏŠ·s—ñ‚Ì‘Ş”ğ

	/* ‘¤–Ê‚ğ•`‚­ (stacks = 1) */
	glTranslated(0.0, 0.0, -half_height);
	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluCylinder(quad, radius, radius, height, sides, 1);

	/* half_height‚Ì‚‚³‚Éã–Ê‚ğ•`‚­ */
	glTranslated(0.0, 0.0, height);
	gluDisk(quad, 0.0, radius, sides, 1);

	/* }Œ`‚ğ— •Ô‚µ‚Ä•`‚­‚æ‚¤‚Éİ’è‚·‚é */
	gluQuadricOrientation(quad, GLU_INSIDE);

	/* -half_height‚Ì‚‚³‚Ì‰º–Ê‚ğ•`‚­ */
	glTranslated(0.0, 0.0, -height);
	gluDisk(quad, 0.0, radius, sides, 1);

	glPopMatrix();			// •ÏŠ·s—ñ‚Ì•œ‹A
}