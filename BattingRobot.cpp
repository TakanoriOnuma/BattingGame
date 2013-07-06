#include <iostream>
#include <math.h>
#include "OpenGL.h"

#include "BattingRobot.h"
#include "MyRobot_BodyParts.h"

#include "MyBat.h"
#include "MaterialData.h"
#include "RobotStateBatting.h"

#include "MyLine.h"

using namespace std;

BattingRobot::BattingRobot(double x, double y, double z)
	: MyRobot(x, y, z)
{
	bat = new MyBat(0.0, -bodyParts->leftArm->getLength(), 0.0);
	bat->move(Vector3d(-0.0, -bat->getRectBox().height, 0.0));
	bat->setMaterialData(MaterialData::createMaterialData(Ore::SILVER));
	bat->setRotateVector(1.0, 0.35, 0.0);
	bat->setAngle(90.0);

	bodyParts->leftArm->setRotateVector(0.0, 1.0, 0.0);
	bodyParts->rightArm->setRotateVector(0.0, 1.0, 0.0);

	bodyParts->leftArm->setAngle(-20.0);
	bodyParts->rightArm->setAngle(20.0);

	bodyParts->leftArm->setBox1Angle(-30.0);
	bodyParts->leftArm->setBox2Angle(-90.0);

	bodyParts->rightArm->setBox1Angle(-30.0);
	bodyParts->rightArm->setBox2Angle(-90.0);

	locus.x = 2.0;
	line = new MyLine(0.0, bodyParts->body->getPoint().y, 0.0, locus.x, locus.y, locus.z);
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
	glTranslated(0.8, 0.0, 0.0);
	bat->draw(false, true);						// batの色を使って描画
	glPopMatrix();								// 責任を持って復帰する
	setMaterial();								// 色をMyRobotの色に戻す

	bodyParts->rightArm->draw(true, false);
	bodyParts->leftLeg->draw(true, false);
	bodyParts->rightLeg->draw(true, false);

	line->draw(true, true);
}

void BattingRobot::update()
{
	if(state != NULL){			// update関数があれば
		state->update(*this);	// それを実行する
	}
	else{						// なかったら
		MyRobot::update();		// superクラスのupdate関数を使う
	}
}

void BattingRobot::swing(const Point3d& target)
{
	if(frame == 0){
		this->target = target;
		state = Batting::getInstance();
		state->init(*this);
	}
}
