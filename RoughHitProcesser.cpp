#include "RoughHitProcesser.h"

#include "MyRobot_BodyParts.h"
#include "MouseManager.h"


// ŠÖ”‚Ì“à•”‚É•Ï”‚ðŽ‚½‚¹‚ÄƒVƒ“ƒOƒ‹ƒgƒ“‚ðŽÀ‘•‚·‚é
Game::RoughHitProcesser* Game::RoughHitProcesser::getInstance()
{
	static RoughHitProcesser roughHitProcesser;
	return &roughHitProcesser;
}

bool Game::RoughHitProcesser::isHit(const MyBall& ball, const BattingRobot& battingRobot) const
{
	if(battingRobot.getFrame() >= BattingRobot::SWING_FRAME / 2 - 5 &&
		battingRobot.getFrame() <= BattingRobot::SWING_FRAME / 2 + 5){

		const Point3d& pt = ball.getPoint();
		const RectBox& box = ball.getRectBox();
		const Point3d& target = battingRobot.getTargetPoint();
		if(pt.x - box.width <= target.x && pt.x + box.width >= target.x &&
			pt.y - box.height <= target.y && pt.y + box.height >= target.y &&
			pt.z - box.length <= target.z && pt.z + box.length >= target.z){

				return true;
		}
	}	

	return false;
}

void Game::RoughHitProcesser::reflect(MyBall& ball, BattingRobot& battingRobot) const
{
	Vector3d move_vec;
	move_vec.x = (ball.getPoint().x - battingRobot.getTargetPoint().x) / ball.getRectBox().width;
	move_vec.y = (ball.getPoint().y - battingRobot.getTargetPoint().y) / ball.getRectBox().height;
	move_vec.z = ball.getRectBox().length - abs(ball.getPoint().z - battingRobot.getTargetPoint().z);

	const Vector3d& vec = ball.getVector();
	ball.setVector(vec.x + move_vec.x, vec.y + move_vec.y, -vec.z - move_vec.z);
}