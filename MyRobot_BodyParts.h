#ifndef ___Class_BodyParts
#define ___Class_BodyParts

#include "MyRobot.h"
#include "MyBox.h"
#include "ArmLeg.h"

// ===== �̂̕��ʂ̍\���� ===== //
struct MyRobot::BodyParts{
	MyBox*  head;			// ��
	MyBox*  body;			// ����
	ArmLeg* leftArm;		// ���r
	ArmLeg* rightArm;		// �E�r
	ArmLeg* leftLeg;		// ����	
	ArmLeg* rightLeg;		// �E��

	BodyParts();
	~BodyParts();
};

#endif