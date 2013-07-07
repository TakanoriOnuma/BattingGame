#include <iostream>

#include "HitProcesser.h"

#include "MyRobot_BodyParts.h"
#include "TriFunction.h"
#include "KeyBoardManager.h"

#include "MyLine.h"

using namespace std;

static void outPoint(string str, const Point3d& pt)
{
	cout << str << "(" << pt.x << ", " << pt.y << ", " << pt.z << ")" << endl;
}

static void outVector(string str, const Vector3d& vec)
{
	cout << str << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << endl;
}

void Game::HitProcesser::hitProcess(MyBall& ball, BattingRobot& battingRobot, MyLine& line)
{
	TriFunction& triFunc = TriFunction::getInstance();

	Point3d bat_pt = battingRobot.getPoint();
	const Point3d& arm_pt = battingRobot.getBodyParts().leftArm->getPoint();
	const double arm_dis = arm_pt.x;		// arm_pt.z = 0�Ȃ���arm_pt.x�����ŋ����ɂȂ�
	const double robot_angle = battingRobot.getAngle();

	// box1�̒��_���W�܂ł̈ړ�
	bat_pt.x += arm_dis * triFunc.t_cos(robot_angle);
	bat_pt.y += arm_pt.y;
	bat_pt.z += arm_dis * triFunc.t_sin(-robot_angle);

	line.setPoint2(bat_pt.x, bat_pt.y, bat_pt.z);

	// box2�̒��_���W�܂ł̈ړ�
	const double arm_angle = battingRobot.getBodyParts().leftArm->getAngle();
	const MyBox* box1 = battingRobot.getBodyParts().leftArm->getBox1();
	const double box1_length = box1->getRectBox().height;
	Vector3d box1_vec;
	box1_vec.x += box1_length * triFunc.t_sin(box1->getAngle());
	box1_vec.y -= box1_length * triFunc.t_cos(box1->getAngle());
	box1_vec.z += box1_length * triFunc.t_cos(arm_angle) * triFunc.t_sin(-box1->getAngle());

	box1_vec.x *= triFunc.t_sin(-robot_angle);
	box1_vec.z *= triFunc.t_cos(robot_angle);

	bat_pt.move(box1_vec);

//	line.setPoint2(bat_pt.x, bat_pt.y, bat_pt.z);

	if(KeyboardManager::getInstance().isPushCharKey(' ')){
		const Point3d& robot_pt = battingRobot.getPoint();
		Point3d box1_pt = battingRobot.getBodyParts().leftArm->getPoint();

		outPoint("robot_pt", robot_pt);
		outPoint("box1_pt", box1_pt);
		outPoint("bat_pt", bat_pt);
		outVector("box1_vec", box1_vec);
		cout << "length:" << box1_length << endl;
	}


	// �{�[�����������Ă���������Ⴄ�Ȃ�
	if(ball.getVector().z < 0.0){
		return;						// ���������I������
	}
	// �o�b�g���X�C���O���Ă��Ȃ��������������I��������B
	// �������̂Ƃ���X�C���O���Ă����Ԃ�m��p���Ȃ��B


	if(isHit(ball, battingRobot)){		// ball��battingRobot��bat���������Ă�����
		reflect(ball, battingRobot);	// �{�[���𒵂˕Ԃ�
	}
}