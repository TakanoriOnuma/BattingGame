#ifndef ___Class_ThrowingBall
#define ___Class_ThrowingBall

#include "PitchingRobotArm.h"

// �ǂ̃N���X���ȉ��̃t�@�C����include���邽��
// ���include����
#include "Rectangle2D.h"
#include "MyBall.h"

class PitchingRobotArm::ThrowingBall{

public:
	virtual ~ThrowingBall(){ }

	virtual void throwBall(const Point3d& throw_point,
		const Rectangle2D* target_field, MyBall& ball) const = 0;
};

#endif