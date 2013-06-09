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

	/* �ʂ̓h��Ԃ����w�肷��(����ł͂Ȃ��A�e�������~����`��) */
	gluQuadricNormals(quad, GLU_SMOOTH);

	glPushMatrix();				// �ϊ��s��̑ޔ�

	/* ���ʂ�`�� (stacks = 1) */
	glTranslated(0.0, 0.0, -half_height);
	gluQuadricOrientation(quad, GLU_OUTSIDE);
	gluCylinder(quad, radius, radius, height, sides, 1);

	/* half_height�̍����ɏ�ʂ�`�� */
	glTranslated(0.0, 0.0, height);
	gluDisk(quad, 0.0, radius, sides, 1);

	/* �}�`�𗠕Ԃ��ĕ`���悤�ɐݒ肷�� */
	gluQuadricOrientation(quad, GLU_INSIDE);

	/* -half_height�̍����̉��ʂ�`�� */
	glTranslated(0.0, 0.0, -height);
	gluDisk(quad, 0.0, radius, sides, 1);

	glPopMatrix();			// �ϊ��s��̕��A
}