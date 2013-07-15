#ifndef ___Class_BallSlowBall
#define ___Class_BallSlowBall

#include "BallVariety.h"

class MyBall::SlowBall : public MyBall::Variety{

public:
	void change(MyBall& ball) const override;
};

#endif