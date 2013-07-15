#include "BallCurve.h"

MyBall::Curve::Curve(double curve_value)
	: curve_value(curve_value)
{
}

void MyBall::Curve::change(MyBall& ball) const
{
	ball.vec.x -= curve_value;
}