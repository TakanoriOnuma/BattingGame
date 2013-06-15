#include <iostream>
#include <math.h>
#include "OpenGL.h"

#include "BattingRobot.h"
#include "MyRobot_BodyParts.h"

#include "MyBat.h"
#include "MaterialData.h"

using namespace std;

BattingRobot::BattingRobot(double x, double y, double z)
	: MyRobot(x, y, z)
{
	bat = new MyBat(0.0, -bodyParts->leftArm->getLength(), 0.0);
	bat->move(Vector3d(0.0, -bat->getRectBox().height, 0.0));
	bat->setMaterialData(MaterialData::createMaterialData(Ore::SILVER));
	bat->setRotateVector(1.0, 0.0, 0.0);
	bat->setAngle(90.0);

	bodyParts->leftArm->setRotateVector(0.0, 1.0, 0.0);
	bodyParts->rightArm->setRotateVector(0.0, 1.0, 0.0);

	bodyParts->leftArm->setAngle(-45.0);
	bodyParts->leftArm->setBox1Angle(-45.0);
	bodyParts->leftArm->setBox2Angle(-30.0);

	bodyParts->rightArm->setAngle(-45.0);
	bodyParts->rightArm->setBox1Angle(-45.0);
	bodyParts->rightArm->setBox2Angle(-30.0);
}

BattingRobot::~BattingRobot()
{
	delete bat;
}

void BattingRobot::draw() const
{
	bodyParts->head->draw(true, false);
	bodyParts->body->draw(true, false);

	glPushMatrix();								// 自分で責任を持って退避する
	bodyParts->leftArm->draw(false, false);		// 退避はしない
	bat->draw(false, true);						// batの色を使って描画
	glPopMatrix();								// 責任を持って復帰する
	setMaterial();								// 色をMyRobotの色に戻す

	bodyParts->rightArm->draw(true, false);
	bodyParts->leftLeg->draw(true, false);
	bodyParts->rightLeg->draw(true, false);
}

void BattingRobot::update()
{
	if(update_function != NULL){		// update関数があれば
		(this->*update_function)();		// それを実行する
	}
	else{						// なかったら
		MyRobot::update();		// superクラスのupdate関数を使う
	}
}

void BattingRobot::swing()
{
	if(frame == 0){
		update_function = &BattingRobot::_swing;
		_swing_init();
	}
}

void BattingRobot::_swing_init()
{
	double angle = 90.0;
	double distance = 0.3;

	double accel_vec = (8.0 + 4.0 * sqrt(5.0)) / (SWING_FRAME * SWING_FRAME);
	double vec = -2.0 * (1.0 + sqrt(5.0)) / SWING_FRAME;

	accel_vec_r = accel_vec * angle;
	vec_r = vec * angle;

//	cout << "accel_vec_r:" << accel_vec_r << ", vec_r:" << vec_r << endl;

	accel_vec_dis.x = 0.0;
	accel_vec_dis.y = 0.0;
//	accel_vec_dis.z = -8.0 * distance / (SWING_FRAME * SWING_FRAME);
	accel_vec_dis.z = -accel_vec * distance;

	vec_dis.x = 0.0;
	vec_dis.y = 0.0;
//	vec_dis.z = 4.0 * distance / SWING_FRAME;
	vec_dis.z = -vec * distance;
	
//	bodyParts->leftArm->move(Vector3d(0.0, 0.0, 0.3));



		bodyParts->leftArm->setAngle(0.0);
		bodyParts->rightArm->setAngle(0.0);

		// 所定の位置に戻る
		Point3d pt = bodyParts->leftArm->getPoint();
		pt.z = 0.0;
		bodyParts->leftArm->move(pt);
		pt.x = bodyParts->rightArm->getPoint().x;
		bodyParts->rightArm->move(pt);

}


void BattingRobot::_swing()
{
	bodyParts->leftArm->addAngle(vec_r);
	bodyParts->rightArm->addAngle(vec_r);
	vec_r += accel_vec_r;

	if(frame < SWING_FRAME - SWING_FRAME / 12){
		bodyParts->leftArm->move(vec_dis);
		bodyParts->rightArm->move(-vec_dis);
	}
	vec_dis += accel_vec_dis;

	frame++;
	if(frame > SWING_FRAME){
		frame = 0;
		update_function = NULL;

	}
}