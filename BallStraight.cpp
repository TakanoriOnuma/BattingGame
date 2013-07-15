#include "BallStraight.h"

MyBall::Straight::Straight(double anti_gravity)
	: anti_gravity(0.0, anti_gravity, 0.0)
{
}

void MyBall::Straight::change(MyBall& ball) const
{
	ball.move(anti_gravity);
}