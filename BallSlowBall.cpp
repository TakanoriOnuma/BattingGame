#include "BallSlowBall.h"

// 特に何もしない
void MyBall::SlowBall::change(MyBall& ball) const
{
	ball.setRotateVector(1.0, 0.0, 0.0);
	ball.addAngle(5.0);
}