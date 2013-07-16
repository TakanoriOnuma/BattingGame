#include "NoDelayHitProcesser.h"

// �֐��̓����ɕϐ����������ăV���O���g������������
Game::NoDelayHitProcesser* Game::NoDelayHitProcesser::getInstance()
{
	static NoDelayHitProcesser noDelayHitProcesser;
	return &noDelayHitProcesser;
}

bool Game::NoDelayHitProcesser::isHit(const MyBall& ball, const BattingRobot& battingRobot) const
{
	if(battingRobot.getFrame() >= 1 &&
		battingRobot.getFrame() <= 5){

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

void Game::NoDelayHitProcesser::reflect(MyBall& ball, BattingRobot& battingRobot) const
{
	Vector3d move_vec;
	move_vec.x = (ball.getPoint().x - battingRobot.getTargetPoint().x) / ball.getRectBox().width;
	move_vec.y = (ball.getPoint().y - battingRobot.getTargetPoint().y) / ball.getRectBox().height;
	move_vec.z = ball.getRectBox().length - abs(ball.getPoint().z - battingRobot.getTargetPoint().z);

	const Vector3d& vec = ball.getVector();
	ball.setVector(vec.x + move_vec.x, vec.y + move_vec.y, -vec.z - move_vec.z);
}