#ifndef ___Class_BodyParts
#define ___Class_BodyParts

#include "MyRobot.h"
#include "MyBox.h"
#include "ArmLeg.h"

// ===== 体の部位の構造体 ===== //
struct MyRobot::BodyParts{
	MyBox*  head;			// 頭
	MyBox*  body;			// 胴体
	ArmLeg* leftArm;		// 左腕
	ArmLeg* rightArm;		// 右腕
	ArmLeg* leftLeg;		// 左足	
	ArmLeg* rightLeg;		// 右足

	BodyParts();
	~BodyParts();
};

#endif