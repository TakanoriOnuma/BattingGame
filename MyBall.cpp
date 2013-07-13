#include "MyBall.h"

MyBall::MyBall(double radius, int sides)
	: MySphere(radius, sides), state(State::HANDED), message(NULL)
{
}

MyBall::MyBall(double x, double y, double z, double radius, int sides)
	: MySphere(x, y, z, radius, sides), state(State::HANDED), message(NULL)
{
}

void MyBall::update()
{
	// 誰かに持たれている状態でなければ
	if(state != State::HANDED){
		move(vec);			// 自分の座標を移動する

		if(vec.z > 0.0){
			vec.y -= 0.001;
		}
		if(vec.z < 0.0){
			vec.y -= 0.01;
		}
	}
}