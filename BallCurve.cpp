#include "BallCurve.h"

MyBall::Curve::Curve(double curve_value)
	: curve_value(curve_value)
{
}

void MyBall::Curve::change(MyBall& ball) const
{
	ball.vec.x -= curve_value;
	if(curve_value > 0.0){
		ball.setRotateVector(0.0, 1.0, 0.0);
		ball.addAngle(-15.0);
	}
	else{
		ball.setRotateVector(0.0, 1.0, 0.0);
		ball.addAngle(15.0);
	}
}