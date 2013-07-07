#ifndef ___Class_RoughHitProcesser
#define ___Class_RoughHitProcesser

#include "HitProcesser.h"

class Game::RoughHitProcesser : public Game::HitProcesser{

protected:
	bool isHit(const MyBall& ball, const BattingRobot& battingRobot) const override;
	void reflect(MyBall& ball, BattingRobot& battingRobot) const override;

public:
	static RoughHitProcesser* getInstance();
};

#endif