#ifndef ___Class_BallStraight
#define ___Class_BallStraight

#include "BallVariety.h"

class MyBall::Straight : public MyBall::Variety{
	double anti_gravity;		// 重力に逆らう力

public:
	Straight(double anti_gravity);

	void change(MyBall& ball) const override;
};

#endif