#include "HitProcesser.h"


void Game::HitProcesser::hitProcess(MyBall& ball, BattingRobot& battingRobot)
{
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