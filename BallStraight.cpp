#include "BallStraight.h"

MyBall::Straight::Straight(double anti_gravity)
	: anti_gravity(anti_gravity)
{
}

void MyBall::Straight::change(MyBall& ball) const
{
	ball.vec.y += anti_gravity;
}