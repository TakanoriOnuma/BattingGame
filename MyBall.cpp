#include "MyBall.h"
#include "BallVariety.h"

MyBall::MyBall(double radius, int sides)
	: MySphere(radius, sides), state(State::HANDED), message(NULL), gravity(0.005), variety(NULL)
{
}

MyBall::MyBall(double x, double y, double z, double radius, int sides)
	: MySphere(x, y, z, radius, sides), state(State::HANDED), message(NULL), gravity(0.005), variety(NULL)
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

void MyBall::emit(Variety* variety)
{
	state = State::ISOLATED;
	if(this->variety != NULL){
		delete this->variety;
	}
	this->variety = variety;	// 球種をセット
	if(message != NULL){
		message->message();		// メッセージを送る
	}

}