#include "MyRobot_BodyParts.h"

// --- コンストラクタ --- //
MyRobot::BodyParts::BodyParts(){
	head     = new MyBox (  0.0,   0.0, 0.0,  0.2, 0.25, 0.22);
	body     = new MyBox (  0.0,  -0.3, 0.0,  0.3,  0.4,  0.6);
	leftArm  = new ArmLeg( 0.28,  -0.3, 0.0, 0.16,  0.4);
	rightArm = new ArmLeg(-0.28,  -0.3, 0.0, 0.16,  0.4);
	leftLeg  = new ArmLeg(  0.1, -0.95, 0.0,  0.2,  0.4);
	rightLeg = new ArmLeg( -0.1, -0.95, 0.0,  0.2,  0.4);
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
