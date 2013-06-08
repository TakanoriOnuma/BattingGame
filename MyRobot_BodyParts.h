#ifndef ___Class_BodyParts
#define ___Class_BodyParts

#include "MyRobot.h"
#include "MyBox.h"
#include "ArmLeg.h"

// ===== ‘Ì‚Ì•”ˆÊ‚Ì\‘¢‘Ì ===== //
struct MyRobot::BodyParts{
	MyBox*  head;			// “ª
	MyBox*  body;			// “·‘Ì
	ArmLeg* leftArm;		// ¶˜r
	ArmLeg* rightArm;		// ‰E˜r
	ArmLeg* leftLeg;		// ¶‘«	
	ArmLeg* rightLeg;		// ‰E‘«

	BodyParts();
	~BodyParts();
};

#endif