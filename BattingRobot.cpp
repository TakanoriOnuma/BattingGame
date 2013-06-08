#include "BattingRobot.h"
#include "MyRobot_BodyParts.h"

#include <math.h>

BattingRobot::BattingRobot(double x, double y, double z)
	: MyRobot(x, y, z)
{
	bodyParts->leftArm->setRotateVector(0.0, 1.0, 0.0);
	bodyParts->rightArm->setRotateVector(0.0, 1.0, 0.0);

	bodyParts->leftArm->setAngle(-45.0);
	bodyParts->leftArm->setBox1Angle(-45.0);
	bodyParts->leftArm->setBox2Angle(-30.0);

}

void BattingRobot::update()
{
	if(update_function != NULL){		// update関数があれば
		(this->*update_function)();		// それを実行する
	}
	else{						// なかったら
		MyRobot::update();		// superクラスのupdate関数を使う
	}
}

void BattingRobot::swing()
{
	if(frame == 0){
		update_function = &BattingRobot::_swing;
		_swing_init();
	}
}

void BattingRobot::_swing_init()
{
	double angle = 90.0;

	accel_vec_r = (8.0 + 4 * sqrt(5.0)) * angle / (SWING_FRAME * SWING_FRAME);
	vec_r = 2.0 * angle / SWING_FRAME - accel_vec_r * SWING_FRAME / 2.0;
	
}


void BattingRobot::_swing()
{
	bodyParts->leftArm->addAngle(vec_r);
	vec_r += accel_vec_r;

	frame++;
	if(frame > SWING_FRAME){
		frame = 0;
		update_function = NULL;
		bodyParts->leftArm->setAngle(0.0);
	}
}