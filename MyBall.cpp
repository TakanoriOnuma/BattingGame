#include "MyBall.h"

MyBall::MyBall()
	: state(State::HANDED)
{
}

void MyBall::update()
{
	// ’N‚©‚É‚½‚ê‚Ä‚¢‚éó‘Ô‚Å‚È‚¯‚ê‚Î
	if(state != State::HANDED){
		move(vec);			// ©•ª‚ÌÀ•W‚ğˆÚ“®‚·‚é
	}
}