#ifndef ___Class_NoDelayHitProcesser
#define ___Class_NoDelayHitProcesser

#include "Game.h"
#include "HitProcesser.h"

class Game::NoDelayHitProcesser : public HitProcesser{

protected:
	bool isHit(const MyBall& ball, const BattingRobot& battingRobot) const override;
	void reflect(MyBall& ball, BattingRobot& battingRobot) const override;

public:
	static NoDelayHitProcesser* getInstance();
};

#endif