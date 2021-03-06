#include "OpenGL.h"

#include "MyCylinder.h"

MyCylinder::MyCylinder(double radius, double height, int sides)
	: DrawableObject(), radius(radius), height(height), sides(sides)
{
	init();
}

MyCylinder::MyCylinder(double x, double y, double z, double radius, double height, int sides)
	: DrawableObject(x, y, z), radius(radius), height(height), sides(sides)
{
	init();
}

void MyCylinder::init()
{
	double diameter = 2 * radius;
	rectBox.setRectBox(diameter, diameter, height);
}

void MyCylinder::draw() const
{
	GLUquadric* quad = quadObject.getQuadric();
	double half_height = height / 2;

	/* 面の塗りつぶしを指定する(線画ではなく陰影をつけた円柱を描く) */
	gluQuadricNormals(quad, GLU_SMOOTH);

	glPushMatrix();				// 変換行列の退避

	/* 側面を描く (stacks = 1) */
	glTranslated(0.0, 0.0, -half_height);
	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluCylinder(quad, radius, radius, height, sides, 1);

	/* half_heightの高さに上面を描く */
	glTranslated(0.0, 0.0, height);
	gluDisk(quad, 0.0, radius, sides, 1);

	/* 図形を裏返して描くように設定する */
	gluQuadricOrientation(quad, GLU_INSIDE);

	/* -half_heightの高さの下面を描く */
	glTranslated(0.0, 0.0, -height);
	gluDisk(quad, 0.0, radius, sides, 1);

	glPopMatrix();			// 変換行列の復帰
}