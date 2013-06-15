#include "ArmLeg.h"
#include "MyBox.h"

ArmLeg::ArmLeg(GLdouble x, GLdouble y, GLdouble z, double girth, double length)
	: DrawObject(x, y, z), girth(girth), length(length), vec_r1(0.0), vec_r2(0.0),
	accel_vec_r1(0.0), accel_vec_r2(0.0)
{
	box1 = new MyBox(0.0, 0.0, 0.0, girth, girth, length);
	box1->setRotateVector(1.0, 0.0, 0.0);
	box2 = new MyBox(0.0, -0.05 - length, 0.0, girth, girth, length);
	box2->setRotateVector(1.0, 0.0, 0.0);

	rectBox.setRectBox(girth, girth, 2 * length + 0.05);
}

ArmLeg::~ArmLeg()
{
	delete box1;
	delete box2;
}

void ArmLeg::draw() const
{
	box1->draw(false, false);		// box1‚ð•`‰æ
	box2->draw(false, false);		// box1‚Æ‘Š‘Î“I‚ÈêŠ‚Ébox2‚ð•`‰æ
}

void ArmLeg::update()
{
	box1->addAngle(vec_r1);
	vec_r1 += accel_vec_r1;
	box2->addAngle(vec_r2);
	vec_r2 += accel_vec_r2;
}

void ArmLeg::setBox1Angle(double angle)
{
	box1->setAngle(angle);
}

void ArmLeg::setBox2Angle(double angle)
{
	box2->setAngle(angle);
}

void ArmLeg::addBox1Angle(double value)
{
	box1->addAngle(value);
}

void ArmLeg::addBox2Angle(double value)
{
	box2->addAngle(value);
}
