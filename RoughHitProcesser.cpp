#include "RoughHitProcesser.h"

#include "MyRobot_BodyParts.h"
#include "MouseManager.h"


#include <iostream>

using namespace std;

// 関数の内部に変数を持たせてシングルトンを実装する
Game::RoughHitProcesser* Game::RoughHitProcesser::getInstance()
{
	static RoughHitProcesser roughHitProcesser;
	return &roughHitProcesser;
}

bool Game::RoughHitProcesser::isHit(const MyBall& ball, const BattingRobot& battingRobot) const
{
	if(battingRobot.getFrame() >= 1 &&
		battingRobot.getFrame() <= 15){
			cout << "check1" << endl;

		const Point3d& pt = ball.getPoint();
		const RectBox& box = ball.getRectBox();
		const Point3d& target = battingRobot.getTargetPoint();
		if(pt.x - box.width / 2 <= target.x && pt.x + box.width / 2 >= target.x &&
			pt.y - box.height / 2 <= target.y && pt.y + box.height / 2 >= target.y &&
			pt.z - box.length <= target.z && pt.z + box.length >= target.z){

				cout << "hit" << endl;
				return true;
		}

	}

	if(2 * BattingRobot::SWING_FRAME / 3 < battingRobot.getFrame() &&
		5 * BattingRobot::SWING_FRAME / 6 > battingRobot.getFrame()){
			cout << "check" << endl;
		
			const Point3d& pt = ball.getPoint();
			const RectBox& box = ball.getRectBox();
			const Point3d& target = battingRobot.getTargetPoint();
			if(pt.x - box.width / 2 <= target.x && pt.x + box.width / 2 >= target.x &&
				pt.y - box.height / 2 <= target.y && pt.y + box.height / 2 >= target.y &&
				pt.z - box.length / 2 <= target.z && pt.z + box.length / 2 >= target.z){

					return true;
			}
	}

	

	return false;
}

void Game::RoughHitProcesser::reflect(MyBall& ball, BattingRobot& battingRobot) const
{
	const Vector3d& vec = ball.getVector();
	ball.setVector(vec.x, vec.y, -vec.z);
}