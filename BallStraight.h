#ifndef ___Class_BallStraight
#define ___Class_BallStraight

#include "BallVariety.h"

class MyBall::Straight : public MyBall::Variety{
	Vector3d anti_gravity;		// èdóÕÇ…ãtÇÁÇ§óÕ

public:
	Straight(double anti_gravity);

	void change(MyBall& ball) const override;
};

#endif