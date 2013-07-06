#include "HitProcesser.h"

#include "MyRobot_BodyParts.h"

#include "MyLine.h"

void Game::HitProcesser::hitProcess(MyBall& ball, BattingRobot& battingRobot, MyLine& line)
{
	Point3d bat_pt = battingRobot.getPoint();
	const Point3d& arm_pt = battingRobot.getBodyParts().leftArm->getPoint();

	bat_pt.x += arm_pt.x;
	bat_pt.y += arm_pt.y;
	bat_pt.z += arm_pt.z;

	line.setPoint2(bat_pt.x, bat_pt.y, bat_pt.z);


	// ボールが向かってくる方向が違うなら
	if(ball.getVector().z < 0.0){
		return;						// 何もせず終了する
	}
	// バットをスイングしていない時も何もせず終了させる。
	// ただ今のところスイングしている状態を知る術がない。


	if(isHit(ball, battingRobot)){		// ballとbattingRobotのbatが当たっていたら
		reflect(ball, battingRobot);	// ボールを跳ね返す
	}
}