#include "RobotStateWalking.h"
#include "MyRobot_BodyParts.h"
#include "TriFunction.h"
#include "KeyboardManager.h"
#include "MyRobotCondition.h"

MyRobot::Walking::Walking()
	: max_frame(-1)		// 未使用
{
}

// 関数の内部に変数を持たせてシングルトンを実装
MyRobot::Walking* MyRobot::Walking::getInstance()
{
	static Walking walking;
	return &walking;
}

void MyRobot::Walking::init(MyRobot& robot) const
{
	double v0 = 2.0 / WALKING_FRAME;	// 第1関節の角速度
	double angle1 = 30.0;
	double angle2 = 20.0;
	double angle3 = 20.0;
	double angle4 = 10.0;
	
	robot.bodyParts->leftArm->setBox1AngleVector(-robot.direction * v0 * angle1);
	robot.bodyParts->leftArm->setBox2AngleVector(-v0 * angle2);

	robot.bodyParts->rightArm->setBox1AngleVector(robot.direction * v0 * angle1);
	robot.bodyParts->rightArm->setBox2AngleVector(-v0 * angle2);

	robot.bodyParts->leftLeg->setBox1AngleVector(robot.direction * v0 * angle3);
	robot.bodyParts->leftLeg->setBox2AngleVector(robot.direction * v0 * angle4);
	robot.bodyParts->leftLeg->setBox2Angle(angle4);

	robot.bodyParts->rightLeg->setBox1AngleVector(-robot.direction * v0 * angle3);
	robot.bodyParts->rightLeg->setBox2AngleVector(-robot.direction * v0 * angle4);
	robot.bodyParts->rightLeg->setBox2Angle(angle4);

	TriFunction& triFunc = TriFunction::getInstance();

	double length = 2 * robot.bodyParts->leftLeg->getLength() / WALKING_FRAME;
	length = length * triFunc.t_sin(30);
	
	robot.vec.x = length * triFunc.t_sin(static_cast<int>(robot.getAngle()));
	robot.vec.z = length * triFunc.t_cos(static_cast<int>(-robot.getAngle()));

}

void MyRobot::Walking::update(MyRobot& robot) const
{
	robot.move(robot.vec);

	robot.bodyParts->leftArm->update();
	robot.bodyParts->rightArm->update();
	robot.bodyParts->leftLeg->update();
	robot.bodyParts->rightLeg->update();
		
	if(robot.frame == WALKING_FRAME / 2){
		robot.bodyParts->leftArm->inverseBox1AngleVector();
		robot.bodyParts->leftArm->inverseBox2AngleVector();

		robot.bodyParts->rightArm->inverseBox1AngleVector();
		robot.bodyParts->rightArm->inverseBox2AngleVector();

		robot.bodyParts->leftLeg->inverseBox1AngleVector();
		robot.bodyParts->leftLeg->inverseBox2AngleVector();

		robot.bodyParts->rightLeg->inverseBox1AngleVector();
		robot.bodyParts->rightLeg->inverseBox2AngleVector();
	}

	robot.frame++;
	if(robot.frame > WALKING_FRAME){
		finish(robot);
	}
}


void MyRobot::Walking::finish(MyRobot& robot) const
{
		robot.frame = 0;
		robot.direction *= -1;		// 方向を反対にする

		// ↑キーが入力されていたら
		if(KeyboardManager::getInstance().isPushSpecialKey(SpecialKey::UP)){
			init(robot);	// また歩かせる
		}
		else{
			robot.condition = Condition::STANDING;
			robot.bodyParts->leftLeg->setBox1Angle(0.0);
			robot.bodyParts->leftLeg->setBox2Angle(0.0);
			robot.bodyParts->rightLeg->setBox1Angle(0.0);
			robot.bodyParts->rightLeg->setBox2Angle(0.0);
			robot.bodyParts->leftArm->setBox1Angle(0.0);
			robot.bodyParts->leftArm->setBox2Angle(0.0);
			robot.bodyParts->rightArm->setBox1Angle(0.0);
			robot.bodyParts->rightArm->setBox2Angle(0.0);

			robot.bodyParts->leftArm->resetVector();
			robot.bodyParts->rightArm->resetVector();
			robot.bodyParts->leftLeg->resetVector();
			robot.bodyParts->rightLeg->resetVector();

			robot.state = NULL;
		}
}