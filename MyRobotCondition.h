#ifndef ___Enum_MyRobotCondition
#define ___Enum_MyRobotCondition

#include "MyRobot.h"

// --- �G���[�Əo�Ă��邯�Ǒ��v --- //
enum class MyRobot::Condition{
	STANDING,		// �������
	RUNNING,		// ������
	SITTING,		// ������
	JUMPING,		// �W�����v���
	WALKING,		// �������
};

#endif