#ifndef ___Class_HitProcesser
#define ___Class_HitProcesser

#include "Game.h"

// どのクラスも以下のファイルはincludeするため
// 先にincludeする
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