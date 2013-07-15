#ifndef ___Class_BallCurve
#define ___Class_BallCurve

#include "BallVariety.h"

class MyBall::Curve : public MyBall::Variety{
	double curve_value;

public:
	Curve(double curve_value);

	void change(MyBall& ball) const override;
};

#endif