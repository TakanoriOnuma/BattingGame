#include <math.h>

#include "RobotStateBatting.h"
#include "MyRobot_BodyParts.h"

BattingRobot::Batting::Batting()
	: max_frame(-1)		// 未使用
{
}

// 関数の内部に変数を持たせてシングルトンを実装する
BattingRobot::Batting* BattingRobot::Batting::getInstance()
{
	static Batting batting;
	return &batting;
}

void BattingRobot::Batting::init(MyRobot& robot) const
{
	// 止むを得ないdynamic_cast。ただし成功は保証する
	// (BattingRobotクラスしかBattingクラスを知らないため)
	BattingRobot& battingRobot = dynamic_cast<BattingRobot&>(robot);

	double angle = 90.0;
	double distance = 0.3;

	double accel_vec = (8.0 + 4.0 * sqrt(5.0)) / (SWING_FRAME * SWING_FRAME);
	double vec = -2.0 * (1.0 + sqrt(5.0)) / SWING_FRAME;

	//double accel_vec = 8.0 / (SWING_FRAME * SWING_FRAME);
	//double vec = -4.0 / SWING_FRAME;

	battingRobot.accel_vec_r = accel_vec * angle;
	battingRobot.vec_r = 180.0 / SWING_FRAME;

	battingRobot.accel_vec_dis.x = 0.0;
	battingRobot.accel_vec_dis.y = 0.0;
	battingRobot.accel_vec_dis.z = 0.0;

	battingRobot.vec_dis.x = 0.0;
	battingRobot.vec_dis.y = 0.0;
	battingRobot.vec_dis.z = -2 * distance / SWING_FRAME;
	

	double angle2 = 20.0;
	double frame_time = SWING_FRAME;
	battingRobot.accel_vec_r2 = -8.0 * angle2 / (frame_time * frame_time);
	battingRobot.vec_r2 = 4.0 * angle2 / frame_time;
	
	battingRobot.bodyParts->leftArm->setBox2Angle(-90.0);
	battingRobot.bodyParts->rightArm->setBox2Angle(-90.0);


	battingRobot.bodyParts->leftArm->setAngle(-20.0 - 90.0);
	battingRobot.bodyParts->rightArm->setAngle(20.0 - 90.0);

	{
		const double angle = 50.0;
		const double frame_time = SWING_FRAME;
		const double accel_angle_vec = -8.0 / (frame_time * frame_time);
		const double angle_vec = 4.0 / frame_time;
		battingRobot.bodyParts->leftArm->setBox2AngleAccelVector(accel_angle_vec * angle);
		battingRobot.bodyParts->leftArm->setBox2AngleVector(angle_vec * angle);
		battingRobot.bodyParts->rightArm->setBox2AngleAccelVector(accel_angle_vec * angle);
		battingRobot.bodyParts->rightArm->setBox2AngleVector(angle_vec * angle);
	}

		// 所定の位置に戻る
		Point3d pt = battingRobot.bodyParts->leftArm->getPoint();
		pt.z = distance;
		battingRobot.bodyParts->leftArm->move(pt);
		pt.x = battingRobot.bodyParts->rightArm->getPoint().x;
		pt.z = -distance;
		battingRobot.bodyParts->rightArm->move(pt);
}

void BattingRobot::Batting::update(MyRobot& robot) const
{
	// 止むを得ないdynamic_cast。ただし成功は保証する
	// (BattingRobotクラスしかBattingクラスを知らないため)
	BattingRobot& battingRobot = dynamic_cast<BattingRobot&>(robot);



	battingRobot.bodyParts->leftArm->addAngle(battingRobot.vec_r);
	battingRobot.bodyParts->rightArm->addAngle(battingRobot.vec_r);

	battingRobot.bodyParts->leftArm->update();
	battingRobot.bodyParts->rightArm->update();


	battingRobot.bodyParts->leftArm->move(battingRobot.vec_dis);
	battingRobot.bodyParts->rightArm->move(-battingRobot.vec_dis);




	if(battingRobot.frame <= SWING_FRAME / 3){
		battingRobot.bodyParts->leftArm->addAngle(battingRobot.vec_r2);
		battingRobot.vec_r2 += battingRobot.accel_vec_r2;
	}

	battingRobot.frame++;
	if(battingRobot.frame > SWING_FRAME){
		finish(battingRobot);
	}


}

void BattingRobot::Batting::finish(MyRobot& robot) const
{
	// 止むを得ないdynamic_cast。ただし成功は保証する
	// (BattingRobotクラスしかBattingクラスを知らないため)
	BattingRobot& battingRobot = dynamic_cast<BattingRobot&>(robot);

	battingRobot.frame = 0;
	battingRobot.state = NULL;

	battingRobot.bodyParts->leftArm->resetVector();
	battingRobot.bodyParts->rightArm->resetVector();

}