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


// ====== フレームごとの動作に使う構造体 ===== //
struct MoveData{
	Vector3d vec;			// 移行状態で移動する量
	double   vec_r1;		// 移行状態で回転するr1
	double   arm_vec_r21;	// 移行状態で腕が回転するr21
	double   arm_vec_r22;	// 移行状態で腕が回転するr22
	double   leg_vec_r21;	// 移行状態で足が回転するr21
	double   leg_vec_r22;	// 移行状態で足が回転するr22
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
	// 大雑把な判定。隙間の考慮がない
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
	// WALKING状態じゃなくて、かつ残っているフレームがないなら
	if(condition != Condition::WALKING && condition != Condition::RUNNING && frame == 0){
		state = Walking::getInstance();		// WALKING状態をセット
		state->init(*this);					// WALKINGの初期化を行う
		condition = Condition::WALKING;		// WALKING状態へ移行する
	}
}

void MyRobot::run()
{
	// RUNNING状態じゃなくて、かつ残っているフレームがないなら
	if(condition != Condition::RUNNING && frame == 0){
		state = Running::getInstance();		// RUNNING状態をセット
		state->init(*this);					// RUNNINGの初期化を行う
		condition = Condition::RUNNING;		// RUNNING状態へ移行する
	}

}
