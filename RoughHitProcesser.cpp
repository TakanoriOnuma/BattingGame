#include "RoughHitProcesser.h"

#include "MyRobot_BodyParts.h"
#include "MouseManager.h"

#include "MyLine.h"

#include <iostream>

using namespace std;

// ŠÖ”‚Ì“à•”‚É•Ï”‚ðŽ‚½‚¹‚ÄƒVƒ“ƒOƒ‹ƒgƒ“‚ðŽÀ‘•‚·‚é
Game::RoughHitProcesser* Game::RoughHitProcesser::getInstance()
{
	static RoughHitProcesser roughHitProcesser;
	return &roughHitProcesser;
}

bool Game::RoughHitProcesser::isHit(const MyBall& ball, const BattingRobot& battingRobot) const
{
	Point3d bat_pt = battingRobot.getPoint();
	const Point3d& arm_pt = battingRobot.getBodyParts().leftArm->getPoint();

	bat_pt.x -= arm_pt.x;
	bat_pt.y -= arm_pt.y;
	bat_pt.z -= arm_pt.z;

	

	return false;
}

void Game::RoughHitProcesser::reflect(MyBall& ball, BattingRobot& battingRobot) const
{

}