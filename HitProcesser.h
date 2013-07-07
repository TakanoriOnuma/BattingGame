#ifndef ___Class_HitProcesser
#define ___Class_HitProcesser

#include "Game.h"

// �ǂ̃N���X���ȉ��̃t�@�C����include���邽��
// ���include����
#include "MyBall.h"
#include "BattingRobot.h"

class Game::HitProcesser{

protected:
	virtual bool isHit(const MyBall& ball, const BattingRobot& battingRobot) const = 0;
	virtual void reflect(MyBall& ball, BattingRobot& battingRobot) const = 0;

public:
	virtual ~HitProcesser(){ }
	void hitProcess(MyBall& ball, BattingRobot& battingRobot);
};


#endif