#include "HitProcesser.h"


void Game::HitProcesser::hitProcess(MyBall& ball, BattingRobot& battingRobot)
{
	// ボールが向かってくる方向が違うなら
	if(ball.getVector().z < 0.0){
		return;						// 何もせず終了する
	}
	// バットをスイングしていない時も何もせず終了させる。
	// ただ今のところスイングしている状態を知る術がない。


	if(isHit(ball, battingRobot)){		// ballとbattingRobotのbatが当たっていたら
		reflect(ball, battingRobot);	// ボールを跳ね返す
	}
}