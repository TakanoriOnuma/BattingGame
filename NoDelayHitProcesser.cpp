#include "NoDelayHitProcesser.h"

#include <iostream>
#include <string>

using namespace std;

static void outVector(string str, const Vector3d& vec)
{
	cout << str << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << endl;
}

// ŠÖ”‚Ì“à•”‚É•Ï”‚ðŽ‚½‚¹‚ÄƒVƒ“ƒOƒ‹ƒgƒ“‚ðŽÀ‘•‚·‚é
Game::NoDelayHitProcesser* Game::NoDelayHitProcesser::getInstance()
{
	static NoDelayHitProcesser noDelayHitProcesser;
	return &noDelayHitProcesser;
}

bool Game::NoDelayHitProcesser::isHit(const MyBall& ball, const BattingRobot& battingRobot) const
{
	if(battingRobot.getFrame() >= 1 &&
		battingRobot.getFrame() <= 5){
			cout << "check1" << endl;

		const Point3d& pt = ball.getPoint();
		const RectBox& box = ball.getRectBox();
		const Point3d& target = battingRobot.getTargetPoint();
		if(pt.x - box.width <= target.x && pt.x + box.width >= target.x &&
			pt.y - box.height <= target.y && pt.y + box.height >= target.y &&
			pt.z - box.length <= target.z && pt.z + box.length >= target.z){

				cout << "hit" << endl;
				return true;
		}
	}	

	return false;
}

void Game::NoDelayHitProcesser::reflect(MyBall& ball, BattingRobot& battingRobot) const
{
	Vector3d move_vec;
	move_vec.x = (ball.getPoint().x - battingRobot.getTargetPoint().x) / ball.getRectBox().width;
	move_vec.y = (ball.getPoint().y - battingRobot.getTargetPoint().y) / ball.getRectBox().height;
	move_vec.z = ball.getRectBox().length - abs(ball.getPoint().z - battingRobot.getTargetPoint().z);
	outVector("move_vec", move_vec);

	const Vector3d& vec = ball.getVector();
	ball.setVector(vec.x + move_vec.x, vec.y + move_vec.y, -vec.z - move_vec.z);
}