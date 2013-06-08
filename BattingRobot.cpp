#include <math.h>
#include "OpenGL.h"

#include "BattingRobot.h"
#include "MyRobot_BodyParts.h"

#include "MyBat.h"
#include "MaterialData.h"

BattingRobot::BattingRobot(double x, double y, double z)
	: MyRobot(x, y, z)
{
	bat = new MyBat(0.0, -bodyParts->leftArm->getLength() - 3.0, 0.0);
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

	glPushMatrix();								// �����ŐӔC�������đޔ�����
	bodyParts->leftArm->draw(false, false);		// �ޔ��͂��Ȃ�
	bat->draw(false, true);						// bat�̐F���g���ĕ`��
	glPopMatrix();								// �ӔC�������ĕ��A����
	setMaterial();								// �F��MyRobot�̐F�ɖ߂�

	bodyParts->rightArm->draw(true, false);
	bodyParts->leftLeg->draw(true, false);
	bodyParts->rightLeg->draw(true, false);
}

void BattingRobot::update()
{
	if(update_function != NULL){		// update�֐��������
		(this->*update_function)();		// ��������s����
	}
	else{						// �Ȃ�������
		MyRobot::update();		// super�N���X��update�֐����g��
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

	accel_vec_r = (8.0 + 4 * sqrt(5.0)) * angle / (SWING_FRAME * SWING_FRAME);
	vec_r = 2.0 * angle / SWING_FRAME - accel_vec_r * SWING_FRAME / 2.0;
	
}


void BattingRobot::_swing()
{
	bodyParts->leftArm->addAngle(vec_r);
	bodyParts->rightArm->addAngle(vec_r);
	vec_r += accel_vec_r;

	frame++;
	if(frame > SWING_FRAME){
		frame = 0;
		update_function = NULL;
		bodyParts->leftArm->setAngle(0.0);
		bodyParts->rightArm->setAngle(0.0);
	}
}