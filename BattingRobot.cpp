#include <iostream>
#include <math.h>
#include "OpenGL.h"

#include "BattingRobot.h"
#include "MyRobot_BodyParts.h"

#include "MyBat.h"
#include "MaterialData.h"
#include "RobotStateBatting.h"

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
}

BattingRobot::~BattingRobot()
{
	delete bat;
}

void BattingRobot::draw() const
{
	bodyParts->head->draw(true, false);
	bodyParts->body->draw(true, false);

	glPushMatrix();								// �����ŐӔC�������đޔ�����
	bodyParts->leftArm->draw(false, false);		// �ޔ��͂��Ȃ�
	glTranslated(0.8, 0.0, 0.0);
	bat->draw(false, true);						// bat�̐F���g���ĕ`��
	glPopMatrix();								// �ӔC�������ĕ��A����
	setMaterial();								// �F��MyRobot�̐F�ɖ߂�

	bodyParts->rightArm->draw(true, false);
	bodyParts->leftLeg->draw(true, false);
	bodyParts->rightLeg->draw(true, false);
}

void BattingRobot::update()
{
	if(state != NULL){			// update�֐��������
		state->update(*this);	// ��������s����
	}
	else{						// �Ȃ�������
		MyRobot::update();		// super�N���X��update�֐����g��
	}
}

void BattingRobot::swing()
{
	if(frame == 0){
		state = Batting::getInstance();
		state->init(*this);
	}
}
