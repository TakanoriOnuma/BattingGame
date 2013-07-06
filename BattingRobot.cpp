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

	glPushMatrix();								// �����ŐӔC�������đޔ�����
	bodyParts->leftArm->draw(false, false);		// �ޔ��͂��Ȃ�
	glTranslated(0.8, 0.0, 0.0);
	bat->draw(false, true);						// bat�̐F���g���ĕ`��
	glPopMatrix();								// �ӔC�������ĕ��A����
	setMaterial();								// �F��MyRobot�̐F�ɖ߂�

	bodyParts->rightArm->draw(true, false);
	bodyParts->leftLeg->draw(true, false);
	bodyParts->rightLeg->draw(true, false);

	line->draw(true, true);
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

void BattingRobot::swing(const Point3d& target)
{
	if(frame == 0){
		this->target = target;
		state = Batting::getInstance();
		state->init(*this);
	}
}
