#ifndef ___Class_NormalThrowingBall
#define ___Class_NormalThrowingBall

#include "ThrowingBall.h"

class PitchingRobotArm::NormalThrowingBall : public PitchingRobotArm::ThrowingBall{

	NormalThrowingBall(){ }
	NormalThrowingBall(const NormalThrowingBall&);

public:

	void setBallVector(const Point3d& throw_point,
		const Rectangle2D* target_field, MyBall& ball) const override;

	static NormalThrowingBall* getInstance();
};

#endif