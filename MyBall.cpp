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
	// �N���Ɏ�����Ă����ԂłȂ����
	if(state != State::HANDED){
		move(vec);			// �����̍��W���ړ�����

		if(vec.z > 0.0){
			vec.y -= 0.001;
		}
		if(vec.z < 0.0){
			vec.y -= 0.01;
		}
	}
}