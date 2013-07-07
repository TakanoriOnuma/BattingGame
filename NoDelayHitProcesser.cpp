#include "NoDelayHitProcesser.h"

#include <iostream>

using namespace std;

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
	const Vector3d& vec = ball.getVector();
	ball.setVector(vec.x, vec.y, -vec.z);
}