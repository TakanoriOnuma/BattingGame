#include "MyBall.h"

MyBall::MyBall()
	: state(State::HANDED)
{
}

void MyBall::update()
{
	// �N���Ɏ�����Ă����ԂłȂ����
	if(state != State::HANDED){
		move(vec);			// �����̍��W���ړ�����
	}
}