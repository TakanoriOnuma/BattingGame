#include "RobotStateRunning.h"
#include "MyRobot_BodyParts.h"
#include "MyRobotCondition.h"
#include "TriFunction.h"
#include "KeyboardManager.h"

MyRobot::Running::Running()
	: max_frame(-1)		// 未使用
{
}

// 関数の内部に変数を持たせてシングルトンを実装する
MyRobot::Running* MyRobot::Running::getInstance()
{
	static Running running;
	return &running;
}

void MyRobot::Running::init(MyRobot& robot) const
{
	double angle1 = 30.0;
	double angle2 = 20.0;
	double angle3 = 30.0;
	double angle4 = 15.0;

	double v0 = 4.0 / RUNNING_FRAME;
	double a  = -8.0 / (RUNNING_FRAME * RUNNING_FRAME);

	robot.bodyParts->leftArm->setBox1AngleAccelVector(-robot.direction * a * angle1);
	robot.bodyParts->leftArm->setBox1AngleVector(-robot.direction * v0 * angle1);
	robot.bodyParts->leftArm->setBox2AngleAccelVector(-robot.direction * a * angle2);
	robot.bodyParts->leftArm->setBox2AngleVector(-robot.direction * v0 * angle2);
	robot.bodyParts->leftArm->setBox2Angle(-angle2);

	robot.bodyParts->rightArm->setBox1AngleAccelVector(robot.direction * a * angle1);
	robot.bodyParts->rightArm->setBox1AngleVector(robot.direction * v0 * angle1);
	robot.bodyParts->rightArm->setBox2AngleAccelVector(robot.direction * a * angle2);
	robot.bodyParts->rightArm->setBox2AngleVector(robot.direction * v0 * angle2);
	robot.bodyParts->rightArm->setBox2Angle(-angle2);


	robot.bodyParts->leftLeg->setBox1AngleAccelVector(robot.direction * a * angle3);
	robot.bodyParts->leftLeg->setBox1AngleVector(robot.direction * v0 * angle3);
	robot.bodyParts->leftLeg->setBox2AngleAccelVector(robot.direction * a * angle4);
	robot.bodyParts->leftLeg->setBox2AngleVector(robot.direction * v0 * angle4);
	robot.bodyParts->leftLeg->setBox2Angle(angle4);
	
	robot.bodyParts->rightLeg->setBox1AngleAccelVector(-robot.direction * a * angle3);
	robot.bodyParts->rightLeg->setBox1AngleVector(-robot.direction * v0 * angle3);
	robot.bodyParts->rightLeg->setBox2AngleAccelVector(-robot.direction * a * angle4);
	robot.bodyParts->rightLeg->setBox2AngleVector(-robot.direction * v0 * angle4);
	robot.bodyParts->rightLeg->setBox2Angle(angle4);

	TriFunction& triFunc = TriFunction::getInstance();
	double length = 2 * robot.bodyParts->leftLeg->getLength() / RUNNING_FRAME;
	robot.vec.x = length * triFunc.t_sin(static_cast<int>(robot.getAngle()));
	robot.vec.z = length * triFunc.t_cos(static_cast<int>(-robot.getAngle()));
}

void MyRobot::Running::update(MyRobot& robot) const
{
	robot.move(robot.vec);

	robot.bodyParts->leftArm->update();
	robot.bodyParts->rightArm->update();
	robot.bodyParts->leftLeg->update();
	robot.bodyParts->rightLeg->update();

	robot.frame++;

	if(robot.frame > RUNNING_FRAME){
		finish(robot);
	}

}

void MyRobot::Running::finish(MyRobot& robot) const
{
		robot.frame = 0;
		robot.direction *= -1;

		// キー入力があったら
		if(KeyboardManager::getInstance().isPushSpecialKey(SpecialKey::UP)){
			init(robot);			// また走らせる
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