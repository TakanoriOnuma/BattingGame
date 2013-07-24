#include "HitProcesser.h"


void Game::HitProcesser::hitProcess(MyBall& ball, BattingRobot& battingRobot)
{
	// ボールが投げられている状態でなければ
	if(ball.getState() != MyBall::State::THROWED){
		return;						// 何もせず終了する
	}
	// バットをスイングしていない時も何もせず終了させる。
	// ただ今のところスイングしている状態を知る術がない。


	if(isHit(ball, battingRobot)){		// ballとbattingRobotのbatが当たっていたら
		reflect(ball, battingRobot);	// ボールを跳ね返す
		ball.hit();						// ボールが打たれる
	}
}