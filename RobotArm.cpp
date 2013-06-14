#include "RobotArm.h"
#include "MyCylinder.h"
#include "MyBox.h"


struct RobotArm::PIMPLE
{
	MyCylinder foundation;		// 土台
	MyBox      first_arm;		// 1番目のアーム
	MyCylinder joint;			// 関節
	MyBox      second_arm;		// 2番目のアーム
	MyBox      hand;			// ハンド

	// --- コンストラクタ --- //
	PIMPLE()
		: foundation(0.0, 0.0, 0.0, 0.5, 0.2, 16),
		first_arm   (0.0, 1.1, 0.0, 0.3, 0.3, 1.0),
		joint       (0.0, 0.1, 0.0, 0.2, 0.4, 16),
		second_arm  (0.0, 1.0, 0.0, 0.3, 0.3, 1.0),
		hand        (0.0, 0.5, 0.0, 0.5, 0.5, 0.5)
	{
	}
};

RobotArm::RobotArm(double x, double y, double z)
	: DrawObject(x, y, z)
{
	pimple = new PIMPLE();
	pimple->foundation.setRotateVector(1.0, 0.0, 0.0);
	pimple->foundation.setAngle(90.0);
	pimple->first_arm.setRotateVector(0.0, 1.0, 0.0);
	pimple->first_arm.setAngle(90.0);
	pimple->joint.setRotateVector(0.0, 0.0, 1.0);

	setRectBox();
}

RobotArm::~RobotArm()
{
	delete pimple;
}

void RobotArm::setRectBox()
{
	const RectBox& foundation_size = pimple->foundation.getRectBox();
	rectBox.length = foundation_size.length;
	rectBox.width  = foundation_size.width;
	rectBox.height = foundation_size.height +
		2 * pimple->first_arm.getRectBox().height +
		pimple->hand.getRectBox().height;
}

void RobotArm::draw() const
{
	pimple->foundation.draw(true, false);
	pimple->first_arm.draw(false, false);
	pimple->joint.draw(false, false);
	pimple->second_arm.draw(false, false);
	pimple->hand.draw(false, false);
}

void RobotArm::addArmAngle(double value)
{
	pimple->joint.addAngle(value);
}

void RobotArm::setArmAngle(double angle)
{
	pimple->joint.setAngle(angle);
}