#include "BallSlowBall.h"

// “Á‚É‰½‚à‚µ‚È‚¢
void MyBall::SlowBall::change(MyBall& ball) const
{
	ball.setRotateVector(1.0, 0.0, 0.0);
	ball.addAngle(5.0);
}