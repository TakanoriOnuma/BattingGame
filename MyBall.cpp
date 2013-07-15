#include "MyBall.h"

MyBall::MyBall(double radius, int sides)
	: MySphere(radius, sides), state(State::HANDED), message(NULL), gravity(0.005)
{
}

MyBall::MyBall(double x, double y, double z, double radius, int sides)
	: MySphere(x, y, z, radius, sides), state(State::HANDED), message(NULL), gravity(0.005)
{
}

void MyBall::update()
{
	// 誰かに持たれている状態でなければ
	if(state != State::HANDED){
		move(vec);			// 自分の座標を移動する

		// ボールを投げている
		if(vec.z > 0.0){
			vec.y -= gravity;
		}
		// 打たれたあと
		else{
			vec.y -= 0.01;
		}
	}
}