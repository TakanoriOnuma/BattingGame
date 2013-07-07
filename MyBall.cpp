#include "MyBall.h"

MyBall::MyBall(double radius, int sides)
	: MySphere(radius, sides), state(State::HANDED)
{
}

MyBall::MyBall(double x, double y, double z, double radius, int sides)
	: MySphere(x, y, z, radius, sides), state(State::HANDED)
{
}

void MyBall::update()
{
	// 誰かに持たれている状態でなければ
	if(state != State::HANDED){
		move(vec);			// 自分の座標を移動する
	}
}