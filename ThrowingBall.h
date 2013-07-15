#ifndef ___Class_ThrowingBall
#define ___Class_ThrowingBall

#include "PitchingRobotArm.h"

// どのクラスも以下のファイルはincludeするため
// 先にincludeする
#include "Rectangle2D.h"
#include "MyBall.h"

class PitchingRobotArm::ThrowingBall{

public:
	virtual ~ThrowingBall(){ }

	virtual void throwBall(const Point3d& throw_point,
		const Rectangle2D* target_field, MyBall& ball) const = 0;
};

#endif