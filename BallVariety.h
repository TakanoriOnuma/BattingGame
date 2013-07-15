#ifndef ___Class_BallVariety
#define ___Class_BallVariety

#include "MyBall.h"

class MyBall::Variety{

public:
	virtual ~Variety(){ }

	virtual void change(MyBall& ball) const = 0;
};


#endif