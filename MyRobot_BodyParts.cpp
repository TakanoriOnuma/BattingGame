#include "MyRobot_BodyParts.h"

// --- コンストラクタ --- //
MyRobot::BodyParts::BodyParts(){
	head     = new MyBox (  0.0,    0.0, 0.0,  0.3, 0.325, 0.33);
	body     = new MyBox (  0.0, -0.425, 0.0, 0.45,   0.6,  0.9);
	leftArm  = new ArmLeg( 0.42, -0.425, 0.0, 0.24,   0.6);
	rightArm = new ArmLeg(-0.42, -0.425, 0.0, 0.24,   0.6);
	leftLeg  = new ArmLeg( 0.15, -1.365, 0.0,  0.3,   0.6);
	rightLeg = new ArmLeg(-0.15, -1.365, 0.0,  0.3,   0.6);
}

// --- デストラクタ --- //
MyRobot::BodyParts::~BodyParts(){
	delete head;
	delete body;
	delete leftArm;
	delete rightArm;
	delete leftLeg;
	delete rightLeg;
}
