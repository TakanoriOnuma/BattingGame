#include "MyBall.h"

MyBall::MyBall()
	: state(State::HANDED)
{
}

void MyBall::update()
{
	// 誰かに持たれている状態でなければ
	if(state != State::HANDED){
		move(vec);			// 自分の座標を移動する
	}
}