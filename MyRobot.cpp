#include <iostream>
#include <math.h>
#include "OpenGL.h"
#include "KeyboardManager.h"
#include "MyRobot.h"
#include "MyRobot_BodyParts.h"

#define PI 3.141592653589793	// ��

using namespace std;

inline double DegToRad(double degree)
{
	return PI * degree / 180;
}

// --- �G���[�Əo�Ă��邯�Ǒ��v --- //
enum class MyRobot::State{
	STANDING,		// �������
	RUNNING,		// ������
	SITTING,		// ������
	JUMPING,		// �W�����v���
	WALKING,		// �������
};

// ====== �t���[�����Ƃ̓���Ɏg���\���� ===== //
struct MoveData{
	Vector3d vec;			// �ڍs��Ԃňړ������
	double   vec_r1;		// �ڍs��Ԃŉ�]����r1
	double   arm_vec_r21;	// �ڍs��ԂŘr����]����r21
	double   arm_vec_r22;	// �ڍs��ԂŘr����]����r22
	double   leg_vec_r21;	// �ڍs��Ԃő�����]����r21
	double   leg_vec_r22;	// �ڍs��Ԃő�����]����r22
};

MyRobot::MyRobot(double x, double y, double z)
	: DrawObject(x, y, z), frame(0), direction(1)
{
	state = State::STANDING;
//	leg   = WalkLeg::LEFT;
	setRotateVector(0.0, 1.0, 0.0);

	bodyParts = new BodyParts();

	update_function = NULL;
}

MyRobot::~MyRobot()
{
	delete bodyParts;
}

void MyRobot::draw() const
{
	bodyParts->head->draw(true, false);
	bodyParts->body->draw(true, false);
	bodyParts->leftArm->draw(true, false);
	bodyParts->rightArm->draw(true, false);
	bodyParts->leftLeg->draw(true, false);
	bodyParts->rightLeg->draw(true, false);
}

void MyRobot::update()
{
	if(update_function != NULL){
		(this->*update_function)();
	}
}

void MyRobot::stand()
{

}



void MyRobot::sit()
{

}


void MyRobot::jump()
{


}


void MyRobot::walk()
{
	// WALKING��Ԃ���Ȃ��āA���c���Ă���t���[�����Ȃ��Ȃ�
	if(state != State::WALKING && state != State::RUNNING && frame == 0){
		update_function = &MyRobot::_walk;		// update�֐����Z�b�g
		_walk_init();					// ������
		state = State::WALKING;			// WALKING��Ԃֈڍs����
	}
}

void MyRobot::_walk_init()
{
	double v0 = 2.0 / WALKING_FRAME;	// ��1�֐߂̊p���x
	double angle1 = 30.0;
	double angle2 = 20.0;
	double angle3 = 20.0;
	double angle4 = 10.0;

	bodyParts->leftArm->setBox1AngleVector(-direction * v0 * angle1);
	bodyParts->leftArm->setBox2AngleVector(-v0 * angle2);

	bodyParts->rightArm->setBox1AngleVector(direction * v0 * angle1);
	bodyParts->rightArm->setBox2AngleVector(-v0 * angle2);

	bodyParts->leftLeg->setBox1AngleVector(direction * v0 * angle3);
	bodyParts->leftLeg->setBox2AngleVector(direction * v0 * angle4);
	bodyParts->leftLeg->setBox2Angle(angle4);

	bodyParts->rightLeg->setBox1AngleVector(-direction * v0 * angle3);
	bodyParts->rightLeg->setBox2AngleVector(-direction * v0 * angle4);
	bodyParts->rightLeg->setBox2Angle(angle4);

/*
	arm_vec_r21 = -2 * 20.0 / WALKING_FRAME;
	arm_vec_r22 = -2 * 30.0 / WALKING_FRAME;
	leg_vec_r21 = 2 * 20.0 / WALKING_FRAME;
	leg_vec_r22 = 0.0;
*/
//	vec_r2 = 2 * 20.0 / WALKING_FRAME;
	double length = 2 * bodyParts->leftLeg->getLength() / WALKING_FRAME;
	length = length * sin(DegToRad(30.0));
//	cout << "length:" << length << endl;
	vec.x = length * sin(DegToRad(this->getAngle()));
	vec.z = length * cos(DegToRad(-this->getAngle()));
}

void MyRobot::_walk()
{
	move(vec);

	bodyParts->leftArm->update();
	bodyParts->rightArm->update();
	bodyParts->leftLeg->update();
	bodyParts->rightLeg->update();

/*
	bodyParts->leftArm->addBox1Angle(vec_r1);
	bodyParts->leftArm->addBox2Angle(arm_vec_r21);	
	bodyParts->rightArm->addBox1Angle(-vec_r1);
	bodyParts->rightArm->addBox2Angle(arm_vec_r22);	

	bodyParts->leftLeg->addBox1Angle(-vec_r1);
	bodyParts->leftLeg->addBox2Angle(-leg_vec_r22);
	bodyParts->rightLeg->addBox1Angle(vec_r1);
	bodyParts->rightLeg->addBox2Angle(leg_vec_r21);
*/

		
	if(frame == WALKING_FRAME / 2){
		bodyParts->leftArm->inverseBox1AngleVector();
		bodyParts->leftArm->inverseBox2AngleVector();

		bodyParts->rightArm->inverseBox1AngleVector();
		bodyParts->rightArm->inverseBox2AngleVector();

		bodyParts->leftLeg->inverseBox1AngleVector();
		bodyParts->leftLeg->inverseBox2AngleVector();

		bodyParts->rightLeg->inverseBox1AngleVector();
//		bodyParts->rightLeg->setBox2AngleVector(4 * 20.0 / WALKING_FRAME);
		bodyParts->rightLeg->inverseBox2AngleVector();
/*
		vec_r1 = -vec_r1;
		arm_vec_r21 = -arm_vec_r21;
		arm_vec_r22 = -arm_vec_r22;
		leg_vec_r21 = -leg_vec_r21;
		leg_vec_r22 = -4 * 20.0 / WALKING_FRAME;
*/
	}

	if(frame == 3 * WALKING_FRAME / 4){
//		bodyParts->rightLeg->inverseBox2AngleVector();
//		leg_vec_r22 = -leg_vec_r22;
	}


	frame++;
	if(frame > WALKING_FRAME){
		frame = 0;
//		swap(bodyParts->leftArm, bodyParts->rightArm);		// ���r����������
//		swap(bodyParts->leftLeg, bodyParts->rightLeg);		// ��������������
		direction *= -1;		// �����𔽑΂ɂ���

		// ���L�[�����͂���Ă�����
		if(KeyboardManager::getKeyboardManager().isPushSpecialKey(SpecialKey::UP)){
			_walk_init();	// �܂���������
		}
		else{
			state = State::STANDING;
			bodyParts->leftLeg->setBox1Angle(0.0);
			bodyParts->leftLeg->setBox2Angle(0.0);
			bodyParts->rightLeg->setBox1Angle(0.0);
			bodyParts->rightLeg->setBox2Angle(0.0);
			bodyParts->leftArm->setBox1Angle(0.0);
			bodyParts->leftArm->setBox2Angle(0.0);
			bodyParts->rightArm->setBox1Angle(0.0);
			bodyParts->rightArm->setBox2Angle(0.0);

			bodyParts->leftArm->resetVector();
			bodyParts->rightArm->resetVector();
			bodyParts->leftLeg->resetVector();
			bodyParts->rightLeg->resetVector();

			update_function = NULL;			// update�֐����Ȃ���
		}
	}

}


void MyRobot::run()
{
	// RUNNING��Ԃ���Ȃ��āA���c���Ă���t���[�����Ȃ��Ȃ�
	if(state != State::RUNNING && frame == 0){
		update_function = &MyRobot::_run;		// update�֐����Z�b�g
		_run_init();					// ������
		state = State::RUNNING;			// WALKING��Ԃֈڍs����
	}

}

void MyRobot::_run_init()
{
	double angle1 = 30.0;
	double angle2 = 20.0;
	double angle3 = 30.0;
	double angle4 = 15.0;

	double v0 = 4.0 / RUNNING_FRAME;
	double a  = -8.0 / (RUNNING_FRAME * RUNNING_FRAME);

	bodyParts->leftArm->setBox1AngleAccelVector(-direction * a * angle1);
	bodyParts->leftArm->setBox1AngleVector(-direction * v0 * angle1);
	bodyParts->leftArm->setBox2AngleAccelVector(-direction * a * angle2);
	bodyParts->leftArm->setBox2AngleVector(-direction * v0 * angle2);
	bodyParts->leftArm->setBox2Angle(-angle2);

	bodyParts->rightArm->setBox1AngleAccelVector(direction * a * angle1);
	bodyParts->rightArm->setBox1AngleVector(direction * v0 * angle1);
	bodyParts->rightArm->setBox2AngleAccelVector(direction * a * angle2);
	bodyParts->rightArm->setBox2AngleVector(direction * v0 * angle2);
	bodyParts->rightArm->setBox2Angle(-angle2);


	bodyParts->leftLeg->setBox1AngleAccelVector(direction * a * angle3);
	bodyParts->leftLeg->setBox1AngleVector(direction * v0 * angle3);
	bodyParts->leftLeg->setBox2AngleAccelVector(direction * a * angle4);
	bodyParts->leftLeg->setBox2AngleVector(direction * v0 * angle4);
	bodyParts->leftLeg->setBox2Angle(angle4);
	
	bodyParts->rightLeg->setBox1AngleAccelVector(-direction * a * angle3);
	bodyParts->rightLeg->setBox1AngleVector(-direction * v0 * angle3);
	bodyParts->rightLeg->setBox2AngleAccelVector(-direction * a * angle4);
	bodyParts->rightLeg->setBox2AngleVector(-direction * v0 * angle4);
	bodyParts->rightLeg->setBox2Angle(angle4);

	double length = 2 * bodyParts->leftLeg->getLength() / RUNNING_FRAME;
//	cout << "length:" << length << endl;
	vec.x = length * sin(DegToRad(this->getAngle()));
	vec.z = length * cos(DegToRad(-this->getAngle()));
}

void MyRobot::_run()
{
	move(vec);

	bodyParts->leftArm->update();
	bodyParts->rightArm->update();
	bodyParts->leftLeg->update();
	bodyParts->rightLeg->update();

	frame++;

	if(frame > RUNNING_FRAME){
		frame = 0;
//		swap(bodyParts->leftArm, bodyParts->rightArm);
//		swap(bodyParts->leftLeg, bodyParts->rightLeg);
		direction *= -1;

		// �L�[���͂���������
		if(KeyboardManager::getKeyboardManager().isPushSpecialKey(SpecialKey::UP)){
			_run_init();		// �܂����点��
		}
		else{
			state = State::STANDING;
			bodyParts->leftLeg->setBox1Angle(0.0);
			bodyParts->leftLeg->setBox2Angle(0.0);
			bodyParts->rightLeg->setBox1Angle(0.0);
			bodyParts->rightLeg->setBox2Angle(0.0);
			bodyParts->leftArm->setBox1Angle(0.0);
			bodyParts->leftArm->setBox2Angle(0.0);
			bodyParts->rightArm->setBox1Angle(0.0);
			bodyParts->rightArm->setBox2Angle(0.0);

			bodyParts->leftArm->resetVector();
			bodyParts->rightArm->resetVector();
			bodyParts->leftLeg->resetVector();
			bodyParts->rightLeg->resetVector();


			update_function = NULL;
		}
	}
}

