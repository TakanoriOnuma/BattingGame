#include "RobotArm.h"
#include "RobotArm_Parts.h"



RobotArm::RobotArm(double x, double y, double z)
	: DrawableObject(x, y, z)
{
	parts = new Parts();
	parts->foundation.setRotateVector(1.0, 0.0, 0.0);
	parts->foundation.setAngle(90.0);
	parts->first_arm.setRotateVector(0.0, 1.0, 0.0);
	parts->first_arm.setAngle(90.0);
	parts->joint.setRotateVector(0.0, 0.0, 1.0);

	setRectBox();
}

RobotArm::~RobotArm()
{
	delete parts;
}

void RobotArm::setRectBox()
{
	const RectBox& foundation_size = parts->foundation.getRectBox();
	rectBox.length = foundation_size.length;
	rectBox.width  = foundation_size.width;
	rectBox.height = foundation_size.height +
		2 * parts->first_arm.getRectBox().height +
		parts->hand.getRectBox().height;
}

void RobotArm::draw() const
{
	parts->foundation.draw(true, false);
	parts->first_arm.draw(false, false);
	parts->joint.draw(false, false);
	parts->second_arm.draw(false, false);
	parts->hand.draw(false, false);
}

void RobotArm::addArmAngle(double value)
{
	parts->joint.addAngle(value);
}

void RobotArm::setArmAngle(double angle)
{
	parts->joint.setAngle(angle);
}