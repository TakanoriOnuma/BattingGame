#include "HitProcesser.h"

#include "MyRobot_BodyParts.h"

#include "MyLine.h"

void Game::HitProcesser::hitProcess(MyBall& ball, BattingRobot& battingRobot, MyLine& line)
{
	Point3d bat_pt = battingRobot.getPoint();
	const Point3d& arm_pt = battingRobot.getBodyParts().leftArm->getPoint();

	bat_pt.x += arm_pt.x;
	bat_pt.y += arm_pt.y;
	bat_pt.z += arm_pt.z;

	line.setPoint2(bat_pt.x, bat_pt.y, bat_pt.z);


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