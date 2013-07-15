#ifndef ___Class_BallStraight
#define ___Class_BallStraight

#include "BallVariety.h"

class MyBall::Straight : public MyBall::Variety{
	double anti_gravity;		// d—Í‚É‹t‚ç‚¤—Í

public:
	Straight(double anti_gravity);

	void change(MyBall& ball) const override;
};

#endif