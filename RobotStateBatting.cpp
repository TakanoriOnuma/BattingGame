#include <math.h>

#include "RobotStateBatting.h"
#include "MyRobot_BodyParts.h"

#include "MyLine.h"

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

		double length = battingRobot.bodyParts->leftArm->getRectBox().height;
		battingRobot.locus.x = -length * 0.8;
		battingRobot.locus.y = 0.0;
		battingRobot.locus.z = 0.0;
		battingRobot.line->setPoint2(battingRobot.locus);

		Point3d robot_pt = battingRobot.getPoint();
		robot_pt.y += battingRobot.bodyParts->body->getPoint().y;
		double dis_y = battingRobot.target.y - robot_pt.y;
		battingRobot.accel_vec_r_y = -8 * dis_y / (battingRobot.SWING_FRAME * battingRobot.SWING_FRAME);
		battingRobot.vec_r_y = 4 * dis_y / battingRobot.SWING_FRAME;

		double dis_z = battingRobot.target.x - robot_pt.x;
		battingRobot.accel_vec_r_z = -8 * dis_z / (battingRobot.SWING_FRAME * battingRobot.SWING_FRAME);
		battingRobot.vec_r_z = 4 * dis_z / battingRobot.SWING_FRAME;
}

void BattingRobot::Batting::update(MyRobot& robot) const
{
	// 止むを得ないdynamic_cast。ただし成功は保証する
	// (BattingRobotクラスしかBattingクラスを知らないため)
	BattingRobot& battingRobot = dynamic_cast<BattingRobot&>(robot);


	battingRobot.locus.x += 0.15;
	battingRobot.locus.y += battingRobot.vec_r_y;
	battingRobot.vec_r_y += battingRobot.accel_vec_r_y;
	battingRobot.locus.z += battingRobot.vec_r_z;
	battingRobot.vec_r_z += battingRobot.accel_vec_r_z;
	battingRobot.line->setPoint2(battingRobot.locus);

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

}