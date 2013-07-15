#include "MyBall.h"
#include "BallVariety.h"
#include "BallStraight.h"

MyBall::MyBall(double radius, int sides)
	: MySphere(radius, sides), state(State::HANDED), message(NULL), gravity(0.005)
{
	variety = new Straight(0.0);		// とりあえず入れておく
}

MyBall::MyBall(double x, double y, double z, double radius, int sides)
	: MySphere(x, y, z, radius, sides), state(State::HANDED), message(NULL), gravity(0.005)
{
	variety = new Straight(0.0);		// とりあえず入れておく
}

void MyBall::update()
{
	// 誰かに持たれている状態でなければ
	if(state != State::HANDED){
		move(vec);			// 自分の座標を移動する

		// ボールを投げている
		if(vec.z > 0.0){
			vec.y -= gravity;
			variety->change(*this);		// ボールによって動きが変わる
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
	delete this->variety;		// 前の球種は削除して
	this->variety = variety;	// 球種をセット
	if(message != NULL){
		message->message();		// メッセージを送る
	}

}