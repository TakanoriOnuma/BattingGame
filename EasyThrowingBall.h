#ifndef ___Class_EasyThrowingBall
#define ___Class_EasyThrowingBall

#include "ThrowingBall.h"

class PitchingRobotArm::EasyThrowingBall : public PitchingRobotArm::ThrowingBall{

	EasyThrowingBall(){ }
	EasyThrowingBall(const EasyThrowingBall&);

public:

	void setBallVector(const Point3d& throw_point,
		const Rectangle2D* target_field, MyBall& ball) const override;

	static EasyThrowingBall* getInstance();
};

#endif