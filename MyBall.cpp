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
	// �N���Ɏ�����Ă����ԂłȂ����
	if(state != State::HANDED){
		move(vec);			// �����̍��W���ړ�����

		// �{�[���𓊂��Ă���
		if(vec.z > 0.0){
			vec.y -= gravity;
		}
		// �ł��ꂽ����
		else{
			vec.y -= 0.01;
		}
	}
}