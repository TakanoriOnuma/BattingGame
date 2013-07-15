#ifndef ___Class_NormalThrowingBall
#define ___Class_NormalThrowingBall

#include "ThrowingBall.h"

class PitchingRobotArm::NormalThrowingBall : public PitchingRobotArm::ThrowingBall{

	// --- “Š‚°‚é‹…Ží --- //
	enum class Variety{
		SLOWBALL,
		STRAIGHT,
		CURVE,

		SIZE,
	};

	NormalThrowingBall(){ }
	NormalThrowingBall(const NormalThrowingBall&);

public:

	void throwBall(const Point3d& throw_point,
		const Rectangle2D* target_field, MyBall& ball) const override;

	static NormalThrowingBall* getInstance();
};

#endif