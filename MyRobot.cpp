#include <iostream>
#include <math.h>
#include "OpenGL.h"
#include "KeyboardManager.h"
#include "MyRobot.h"
#include "MyRobot_BodyParts.h"
#include "RobotState.h"
#include "MyRobotCondition.h"
#include "RobotStateWalking.h"
#include "RobotStateRunning.h"

using namespace std;


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
	: DrawableObject(x, y, z), frame(0), direction(1)
{
	condition = Condition::STANDING;
	setRotateVector(0.0, 1.0, 0.0);

	bodyParts = new BodyParts();

	state = NULL;

	setRectBox();
}

MyRobot::~MyRobot()
{
	delete bodyParts;
}

void MyRobot::setRectBox()
{
	// ��G�c�Ȕ���B���Ԃ̍l�����Ȃ�
	const RectBox& head_size = bodyParts->head->getRectBox();
	const RectBox& body_size = bodyParts->body->getRectBox();
	const RectBox& arm_size  = bodyParts->leftArm->getRectBox();
	const RectBox& leg_size  = bodyParts->leftLeg->getRectBox();

	rectBox.length = body_size.length;
	rectBox.width  = body_size.width + 2 * arm_size.width;
	rectBox.height = head_size.height + body_size.height + leg_size.height;
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
	if(state != NULL){
		state->update(*this);
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
	if(condition != Condition::WALKING && condition != Condition::RUNNING && frame == 0){
		state = Walking::getInstance();		// WALKING��Ԃ��Z�b�g
		state->init(*this);					// WALKING�̏��������s��
		condition = Condition::WALKING;		// WALKING��Ԃֈڍs����
	}
}

void MyRobot::run()
{
	// RUNNING��Ԃ���Ȃ��āA���c���Ă���t���[�����Ȃ��Ȃ�
	if(condition != Condition::RUNNING && frame == 0){
		state = Running::getInstance();		// RUNNING��Ԃ��Z�b�g
		state->init(*this);					// RUNNING�̏��������s��
		condition = Condition::RUNNING;		// RUNNING��Ԃֈڍs����
	}

}
